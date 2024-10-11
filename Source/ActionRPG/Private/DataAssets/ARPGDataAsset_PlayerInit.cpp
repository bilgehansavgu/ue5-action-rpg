// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/ARPGDataAsset_PlayerInit.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "GAS/ARPGPlayerGameplayAbility.h"
#include "Types/ARPGStructTypes.h"
#include "GameplayEffect.h"


void UARPGDataAsset_PlayerInit::GrantDefaultAbilities(
	UAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel) const
{
	check(AbilitySystemComponent);

	GrantAbilitiesFromArray(ActivateOnGivenAbilities, AbilitySystemComponent, ApplyLevel);
	GrantAbilitiesFromArray(ReactiveAbilities, AbilitySystemComponent, ApplyLevel);

	if (!InitGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect> EffectClass : InitGameplayEffects)
		{
			if (!EffectClass) continue;

			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();

			AbilitySystemComponent->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, AbilitySystemComponent->MakeEffectContext());
		}
	}
	
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

void UARPGDataAsset_PlayerInit::GrantAbilitiesFromArray(
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
