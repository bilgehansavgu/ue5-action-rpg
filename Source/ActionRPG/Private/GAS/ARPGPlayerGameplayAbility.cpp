// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ARPGPlayerGameplayAbility.h"

#include "Characters/ARPGCharacterBeard.h"
#include "GameModes/ARPGPlayerController.h"

AARPGCharacterBeard* UARPGPlayerGameplayAbility::GetBeardCharacterFromActorInfo()
{
	if (!CachedCharacter.IsValid())
	{
		CachedCharacter = Cast<AARPGCharacterBeard>(CurrentActorInfo->AvatarActor);
	}
   
	return CachedCharacter.IsValid()? CachedCharacter.Get() : nullptr;
}

AARPGPlayerController* UARPGPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<AARPGPlayerController>(CurrentActorInfo->PlayerController);
	}
	return CachedPlayerController.IsValid()? CachedPlayerController.Get() : nullptr;
}

UARPGPlayerCombatComponent* UARPGPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return GetBeardCharacterFromActorInfo()->GetCombatComponent();
}
