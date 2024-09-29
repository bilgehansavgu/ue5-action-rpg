// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionRPG/Public/Characters/ARPGCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/ARPGActionComponent.h"
#include "Components/ARPGAttributeComponent.h"
#include "Components/ARPGInteractionComponent.h"
#include "Components/ARPGInventoryComponent.h"

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

	// Action Component
	ActionComponent = CreateDefaultSubobject<UARPGActionComponent>("ActionComponent");

	// Inventory Component
	InventoryComponent = CreateDefaultSubobject<UARPGInventoryComponent>("InventoryComponent");
}

void AARPGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComponent->OnHealthChanged.AddUniqueDynamic(this, &ThisClass::OnHealthChangedEvent);
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
	EnhancedInputComponent->BindAction(Input_BasicAttack, ETriggerEvent::Triggered, this, &ThisClass::BasicRangedAttack);
	EnhancedInputComponent->BindAction(Input_AreaOfEffect, ETriggerEvent::Triggered, this, &ThisClass::AreaOfEffectAttack);
	EnhancedInputComponent->BindAction(Input_Teleport, ETriggerEvent::Triggered, this, &ThisClass::Teleport);
	EnhancedInputComponent->BindAction(Input_EquipWeapon, ETriggerEvent::Triggered, this, &ThisClass::EquipMainWeapon);
	EnhancedInputComponent->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ThisClass::Interact);
	//EnhancedInputComponent->BindAction(Input_DropWeapon, ETriggerEvent::Triggered, this, &ThisClass::DropWeapon);
	EnhancedInputComponent->BindAction(Input_ToggleInventory, ETriggerEvent::Triggered, this, &ThisClass::ToggleInventory);
	EnhancedInputComponent->BindAction(Input_Sprint, ETriggerEvent::Started, this, &ThisClass::Sprint);
	EnhancedInputComponent->BindAction(Input_Sprint, ETriggerEvent::Completed, this, &ThisClass::StopSprint);
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

void AARPGCharacter::BasicRangedAttack()
{
	ActionComponent->StartActionByName(this, "BasicRangedAttack");
}

void AARPGCharacter::AreaOfEffectAttack()
{
	ActionComponent->StartActionByName(this, "AreaOfEffectAttack");
}

void AARPGCharacter::Teleport()
{
	ActionComponent->StartActionByName(this, "Teleport");
}

void AARPGCharacter::EquipMainWeapon()
{
	InventoryComponent->ToggleMainWeaponMontage(this);
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
	InventoryComponent->ToggleInventoryWidget(this);
}


void AARPGCharacter::Sprint()
{
	ActionComponent->StartActionByName(this, "Sprint");
}

void AARPGCharacter::StopSprint()
{
	ActionComponent->StopActionByName(this, "Sprint");
}
