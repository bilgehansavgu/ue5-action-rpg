// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/ARPGDataAsset_CharacterStartData.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "GAS/ARPGGameplayAbility.h"

bool FARPGPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

void UARPGDataAsset_CharacterStartData::GiveToAbilitySystemComponent(
	UAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel) const
{
	check(AbilitySystemComponent);

	GrantAbilities(ActivateOnGivenAbilities, AbilitySystemComponent, ApplyLevel);
	GrantAbilities(ReactiveAbilities, AbilitySystemComponent, ApplyLevel);
}

void UARPGDataAsset_CharacterStartData::GrantAbilities(
	TArray<TSubclassOf<UARPGGameplayAbility>> Abilities,
	UAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel) const
{
	if (Abilities.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UARPGGameplayAbility>& Ability : Abilities)
	{
		if(!Ability) continue;
		
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = AbilitySystemComponent->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}
