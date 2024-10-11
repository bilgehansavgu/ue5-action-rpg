// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGCharacterBeard.h"

#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/ARPGAbilitySystemComponent.h"
#include "Components/ARPGInputComponent.h"
#include "Components/ARPGPlayerCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "DataAssets/ARPGDataAsset_PlayerInit.h"
#include "DataAssets/ARPGDataAsset_InputConfig.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/APRGGameplayTags.h"
#include "GAS/ARPGAttributeSet.h"

class UARPGInputComponent;
class UEnhancedInputLocalPlayerSubsystem;

AARPGCharacterBeard::AARPGCharacterBeard()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f,96.f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f,55.f,65.f);
	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,500.f,0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	AbilitySystemComponent = CreateDefaultSubobject<UARPGAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UARPGAttributeSet>("AttributeSet");

	CombatComponent = CreateDefaultSubobject<UARPGPlayerCombatComponent>("PlayerCombatComponent");

}

void AARPGCharacterBeard::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARPGCharacterBeard::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterInitDataAsset.IsNull())
	{
		if (UARPGDataAsset_PlayerInit* LoadedData = CharacterInitDataAsset.LoadSynchronous())
		{
			LoadedData->GrantDefaultAbilities(AbilitySystemComponent);
		}
	}

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this,this);

		ensureAlwaysMsgf(!CharacterInitDataAsset.IsNull(),TEXT("No start up data for %s"),*GetName());
	}
	
}

void AARPGCharacterBeard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset,TEXT("No valid data asset as input config"));
	
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	
	Subsystem->AddMappingContext(InputConfigDataAsset->MappingContext,0);
	
	UARPGInputComponent* ARPGInputComponent = CastChecked<UARPGInputComponent>(PlayerInputComponent);
	
	ARPGInputComponent->BindNativeInputAction(InputConfigDataAsset,ARPGGameplayTags::Input_Move,ETriggerEvent::Triggered,this,&ThisClass::Input_Move);
	ARPGInputComponent->BindNativeInputAction(InputConfigDataAsset,ARPGGameplayTags::Input_Look,ETriggerEvent::Triggered,this,&ThisClass::Input_Look);
	ARPGInputComponent->BindAbilityInputActions(InputConfigDataAsset,this,&ThisClass::Input_AbilityInputPressed,&ThisClass::Input_AbilityInputReleased);
}

void AARPGCharacterBeard::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f,Controller->GetControlRotation().Yaw,0.f);
	
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection,MovementVector.Y);
	}
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection,MovementVector.X);
	}
}

void AARPGCharacterBeard::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AARPGCharacterBeard::Input_AbilityInputPressed(FGameplayTag InputTag)
{
	AbilitySystemComponent->OnAbilityInputPressed(InputTag);
}

void AARPGCharacterBeard::Input_AbilityInputReleased(FGameplayTag InputTag)
{
}
