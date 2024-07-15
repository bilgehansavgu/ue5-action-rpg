// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionRPG/Public/Core/Characters/ARPGCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Core/Equippables/ARPGBaseEquippable.h"

AARPGCharacter::AARPGCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationYaw = false;
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
	EnhancedInputComponent->BindAction(Input_EquipWeapon, ETriggerEvent::Triggered, this, &ThisClass::ToggleMainWeapon);
}

void AARPGCharacter::SpawnWeapon()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;
	SpawnParameters.Owner = this;

	FTransform HipSpawnTransform = GetMesh()->GetSocketTransform(BigSwordHipLSocketName);
	
	MainWeapon = GetWorld()->SpawnActor<AActor>(WeaponClass, HipSpawnTransform, SpawnParameters);
	Cast<AARPGBaseEquippable>(MainWeapon)->OnUnequipped(BigSwordHipLSocketName);
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

void AARPGCharacter::ToggleMainWeapon()
{
	if(!Cast<AARPGBaseEquippable>(MainWeapon)->IsEquipped)
	{
		Cast<AARPGBaseEquippable>(MainWeapon)->OnEquipped(BigSwordHandRSocketName);
	} else
	{
		Cast<AARPGBaseEquippable>(MainWeapon)->OnUnequipped(BigSwordHipLSocketName);
	}
}

void AARPGCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
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

		FVector TraceStart = CameraComponent->GetComponentLocation();
		FVector TraceEnd = CameraComponent->GetComponentLocation() + (GetControlRotation().Vector() * ProjectileTraceEndDistance);

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
