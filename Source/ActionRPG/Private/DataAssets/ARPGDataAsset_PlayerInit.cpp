// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/ARPGDataAsset_PlayerInit.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "GAS/ARPGPlayerGameplayAbility.h"
#include "Types/ARPGStructTypes.h"


void UARPGDataAsset_PlayerInit::GiveToAbilitySystemComponent(
	UAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel) const
{
	check(AbilitySystemComponent);

	GrantAbilities(ActivateOnGivenAbilities, AbilitySystemComponent, ApplyLevel);
	GrantAbilities(ReactiveAbilities, AbilitySystemComponent, ApplyLevel);
	
	for (const FARPGPlayerTaggedAbility& AbilityWithInputTag : PlayerStartTaggedGameplayAbility)
	{
		if (!AbilityWithInputTag.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilityWithInputTag.Ability);
		AbilitySpec.SourceObject = AbilitySystemComponent->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityWithInputTag.InputTag);
		
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void UARPGDataAsset_PlayerInit::GrantAbilities(
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
