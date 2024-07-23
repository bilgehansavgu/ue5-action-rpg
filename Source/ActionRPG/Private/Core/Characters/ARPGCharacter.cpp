// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionRPG/Public/Core/Characters/ARPGCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/ARPGAttributeComponent.h"
#include "Components/ARPGInteractionComponent.h"
#include "Core/Equippables/ARPGBaseEquippable.h"
#include "Core/Projectiles/ARPGProjectileBase.h"
#include "Kismet/GameplayStatics.h"

AARPGCharacter::AARPGCharacter()
{
	//	SpringArm & Camera Components
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	//	Movement Component
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	//	Interaction Component
	InteractionComponent = CreateDefaultSubobject<UARPGInteractionComponent>("InteractionComponent");

	// Character Attributes Component
	AttributeComponent = CreateDefaultSubobject<UARPGAttributeComponent>("AttributeComponent");

	AttributeComponent->OnHealthChanged.AddUniqueDynamic(this, &ThisClass::OnHealthChangedEvent);
}

void AARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnWeapon();
}

void AARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* PlayerController = GetController<APlayerController>();
	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if(!LocalPlayerSubsystem)
	{
		return;
	}

	LocalPlayerSubsystem->ClearAllMappings();

	LocalPlayerSubsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInputComponent->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(Input_LookMouse, ETriggerEvent::Triggered, this, &ThisClass::LookMouse);
	EnhancedInputComponent->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(Input_BasicAttack, ETriggerEvent::Triggered, this, &ThisClass::BasicAttack);
	EnhancedInputComponent->BindAction(Input_AreaOfEffect, ETriggerEvent::Triggered, this, &ThisClass::AreaOfEffectAttack);
	EnhancedInputComponent->BindAction(Input_Teleport, ETriggerEvent::Triggered, this, &ThisClass::Teleport);
	EnhancedInputComponent->BindAction(Input_EquipWeapon, ETriggerEvent::Triggered, this, &ThisClass::ToggleMainWeaponMontage);
	EnhancedInputComponent->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ThisClass::Interact);
}

void AARPGCharacter::SpawnWeapon()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;
	SpawnParameters.Owner = this;

	FTransform HipSpawnTransform = GetMesh()->GetSocketTransform(BigSwordHipLSocketName);
	
	MainWeapon = GetWorld()->SpawnActor<AARPGBaseEquippable>(WeaponClass, HipSpawnTransform, SpawnParameters);
	MainWeapon->OnUnequipped(BigSwordHipLSocketName);
}

void AARPGCharacter::Move(const FInputActionInstance& Instance)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.f;
	ControlRotation.Roll = 0.f;

	const FVector2D AxisValues = Instance.GetValue().Get<FVector2D>();

	const FVector ForwardVector = ControlRotation.Vector();
	const FVector RightVector = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, AxisValues.Y);

	AddMovementInput(RightVector, AxisValues.X);
}

void AARPGCharacter::LookMouse(const FInputActionValue& Value)
{
	const FVector2D InputVector = Value.Get<FVector2D>();

	if(!InputVector.IsNearlyZero())
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

void AARPGCharacter::ToggleMainWeaponMontage()
{
	if (bIsWeaponEquipped)
	{
		PlayAnimMontage(PutBackWeaponAnimation);
		bIsWeaponEquipped = false;
	} else
	{
		PlayAnimMontage(DrawWeaponAnimation);
		bIsWeaponEquipped = true;
	}
	
}

void AARPGCharacter::OnHealthChangedEvent(AActor* InstigatorActor,
	UARPGAttributeComponent* OwningComponent, float NewHealth, float DeltaHealth)
{
	if(DeltaHealth < 0.f)
	{
		TookDamageMaterialEffect();
	} else if (DeltaHealth > 0.f)
	{
		HPBuffMaterialEffect();
	}
}

void AARPGCharacter::TookDamageMaterialEffect() const
{
	GetMesh()->SetScalarParameterValueOnMaterials("HitTime", GetWorld()->TimeSeconds);

	FVector3d FlashColor = FVector3d(1.0f, 0.0f, 0.0f);
	GetMesh()->SetVectorParameterValueOnMaterials("Flash Color", FlashColor);
}

void AARPGCharacter::HPBuffMaterialEffect() const
{
	GetMesh()->SetScalarParameterValueOnMaterials("HitTime", GetWorld()->TimeSeconds);

	FVector3d FlashColor = FVector3d(0.0f, 1.0f, 0.0f);
	GetMesh()->SetVectorParameterValueOnMaterials("Flash Color", FlashColor);
}

void AARPGCharacter::DrawWeapon() const
{
	Cast<AARPGBaseEquippable>(MainWeapon)->OnEquipped(BigSwordHandRSocketName);
}

void AARPGCharacter::PutBackWeapon() const
{
	Cast<AARPGBaseEquippable>(MainWeapon)->OnUnequipped(BigSwordHipLSocketName);
}

void AARPGCharacter::SpawnProjectile(TSubclassOf<AARPGProjectileBase> ClassToSpawn)
{
	if(ensureAlways(ClassToSpawn))
	{
		FVector RightHandSpawnLocation = GetMesh()->GetSocketLocation(RightHandSocketName);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(ProjectileTraceRadius);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if(PlayerController == nullptr)
		{
			return;
		}

		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		FVector2D ScreenCenter = ViewportSize / 2.f;
	
		FVector WorldLocation, WorldDirection;
		UGameplayStatics::DeprojectScreenToWorld(PlayerController, ScreenCenter, WorldLocation, WorldDirection);
	
		FVector TraceStart = WorldLocation;
		FVector TraceEnd = WorldLocation + (WorldDirection * ProjectileTraceEndDistance);

		FHitResult HitResult;

		if(GetWorld()->SweepSingleByObjectType(HitResult, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, Shape, Params))
		{
			TraceEnd = HitResult.ImpactPoint;
		}

		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - RightHandSpawnLocation).Rotator();

		FTransform SpawnTransform = FTransform(ProjRotation, RightHandSpawnLocation);
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTransform, SpawnParameters);
	}
}

void AARPGCharacter::BasicAttack()
{
	SpawnProjectile(BasicAttackProjectileClass);
}

void AARPGCharacter::AreaOfEffectAttack()
{
	SpawnProjectile(AreaOfEffectClass);
}

void AARPGCharacter::Teleport()
{
	SpawnProjectile(TeleportSpellClass);
}

void AARPGCharacter::Interact()
{
	if(InteractionComponent)
	{
		InteractionComponent->Interact();
	}
}
