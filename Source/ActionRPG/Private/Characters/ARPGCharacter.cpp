// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionRPG/Public/Characters/ARPGCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/ARPGActionComponent.h"
#include "Components/ARPGAttributeComponent.h"
#include "Components/ARPGInteractionComponent.h"
#include "Equippables/ARPGBaseEquippable.h"
#include "Equippables/ARPGBaseWeapon.h"
#include "Projectiles/ARPGProjectileBase.h"
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

	ActionComponent = CreateDefaultSubobject<UARPGActionComponent>("ActionComponent");
}

void AARPGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComponent->OnHealthChanged.AddUniqueDynamic(this, &ThisClass::OnHealthChangedEvent);

	InventoryWidget = CreateWidget<UUserWidget>(GetWorld(), InventoryWidgetClass);
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
	//EnhancedInputComponent->BindAction(Input_DropWeapon, ETriggerEvent::Triggered, this, &ThisClass::DropWeapon);
	EnhancedInputComponent->BindAction(Input_ToggleInventory, ETriggerEvent::Triggered, this, &ThisClass::ToggleInventory);
	EnhancedInputComponent->BindAction(Input_Sprint, ETriggerEvent::Started, this, &ThisClass::Sprint);
	EnhancedInputComponent->BindAction(Input_Sprint, ETriggerEvent::Completed, this, &ThisClass::StopSprint);
}

void AARPGCharacter::PickUpWeapon(TSubclassOf<AARPGBaseEquippable> WeaponClass)
{
	if (!WeaponClass)
	{
		return;
	}

	if (GetMainWeapon() != nullptr)
	{
		MainWeapon->Destroy();
	}
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;
	SpawnParameters.Owner = this;
	
	MainWeapon = GetWorld()->SpawnActor<AARPGBaseEquippable>(WeaponClass, GetTransform(), SpawnParameters);

	Cast<AARPGBaseWeapon>(MainWeapon)->OnEquipped(this);
	
	bIsWeaponEquipped = true;
}

// void AARPGCharacter::DropWeapon()
// {
// 	if (GetMainWeapon() == nullptr)
// 	{
// 		return;
// 	}
//
// 	UClass* WeaponClass = GetMainWeapon()->GetClass();
//
// 	FActorSpawnParameters SpawnParameters;
// 	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
// 	
// 	AARPGWeaponPickupActor* PickUpActor = GetWorld()->SpawnActor<AARPGWeaponPickupActor>(AARPGWeaponPickupActor::StaticClass(), GetTransform(), SpawnParameters);
// 	PickUpActor->SetEquippableClass(WeaponClass);
// 	
// 	MainWeapon->Destroy();
// }

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
	if (!MainWeapon)
	{
		return;
	}
	if (AARPGBaseWeapon* Weapon = Cast<AARPGBaseWeapon>(MainWeapon))
	{
		if (bIsWeaponEquipped)
		{
			PlayAnimMontage(Weapon->GetDisarmAnimationMontage());
			bIsWeaponEquipped = false;
		} else
		{
			PlayAnimMontage(Weapon->GetDrawAnimationMontage());
			bIsWeaponEquipped = true;
		}
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

void AARPGCharacter::TookDamageMaterialEffect()
{
	GetMesh()->SetScalarParameterValueOnMaterials("HitTime", GetWorld()->TimeSeconds);

	FVector3d FlashColor = FVector3d(1.0f, 0.0f, 0.0f);
	GetMesh()->SetVectorParameterValueOnMaterials("Flash Color", FlashColor);
}

void AARPGCharacter::HPBuffMaterialEffect()
{
	GetMesh()->SetScalarParameterValueOnMaterials("HitTime", GetWorld()->TimeSeconds);

	FVector3d FlashColor = FVector3d(0.0f, 1.0f, 0.0f);
	GetMesh()->SetVectorParameterValueOnMaterials("Flash Color", FlashColor);
}

void AARPGCharacter::DrawWeapon()
{
	if (AARPGBaseWeapon* Weapon = Cast<AARPGBaseWeapon>(MainWeapon))
	{
		Weapon->OnEquipped(this);
	}
}

AARPGBaseEquippable* AARPGCharacter::GetMainWeapon()
{
	return MainWeapon;
}

void AARPGCharacter::SetMainWeapon(AARPGBaseEquippable* Weapon)
{
	MainWeapon = Weapon;
}

void AARPGCharacter::PutBackWeapon()
{
	if (AARPGBaseWeapon* Weapon = Cast<AARPGBaseWeapon>(MainWeapon))
	{
		Weapon->OnUnequipped(this);
	}
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

void AARPGCharacter::ToggleInventory()
{
	if (bIsInventoryOpen)
	{
		if (InventoryWidget)
		{
			InventoryWidget->RemoveFromParent();
		}

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->SetShowMouseCursor(false);
		}
	}
	else
	{
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
		}

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
			PlayerController->SetInputMode(InputMode);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	bIsInventoryOpen = !bIsInventoryOpen;
}

void AARPGCharacter::Sprint()
{
	ActionComponent->StartActionByName(this, "Sprint");
}

void AARPGCharacter::StopSprint()
{
	ActionComponent->StopActionByName(this, "Sprint");
}
