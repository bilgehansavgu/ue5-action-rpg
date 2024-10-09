// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ARPGFoeGameplayAbility.h"

#include "Characters/ARPGCharacterFoe.h"
#include "Components/ARPGFoeCombatComponent.h"

AARPGCharacterFoe* UARPGFoeGameplayAbility::GetFoeCharacterFromActorInfo()
{
	if (!CachedFoeCharacter.IsValid())
	{
		CachedFoeCharacter = Cast<AARPGCharacterFoe>(CurrentActorInfo->AvatarActor);
	}

	return CachedFoeCharacter.IsValid() ? CachedFoeCharacter.Get() : nullptr;
}

UARPGFoeCombatComponent* UARPGFoeGameplayAbility::GetFoeCombatComponentFromActorInfo()
{
	return GetFoeCharacterFromActorInfo()->GetFoeCombatComponent();
}
