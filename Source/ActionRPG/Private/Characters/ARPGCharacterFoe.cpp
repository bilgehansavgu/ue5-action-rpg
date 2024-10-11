// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGCharacterFoe.h"

#include "ActionRPG/ARPGDebugHelper.h"
#include "Components/ARPGAbilitySystemComponent.h"
#include "Components/ARPGFoeCombatComponent.h"
#include "DataAssets/ARPGDataAsset_FoeInit.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

AARPGCharacterFoe::AARPGCharacterFoe()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,180.f,0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;
	
	FoeCombatComponent = CreateDefaultSubobject<UARPGFoeCombatComponent>("FoeCombatComponent");
	AbilitySystemComponent = CreateDefaultSubobject<UARPGAbilitySystemComponent>("AbilitySystemComponent");
}

void AARPGCharacterFoe::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitData();
}

void AARPGCharacterFoe::InitData()
{
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		FoeInitDataAsset.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UARPGDataAsset_FoeInit* LoadedData = FoeInitDataAsset.Get())
				{
					LoadedData->GrantDefaultAbilities(AbilitySystemComponent);

					Debug::Print("Foe data asset loaded successfully", FColor::Green);
				}
			}
		)
	);
}
