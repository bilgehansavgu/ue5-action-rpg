// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/ARPGDataAsset_FoeInit.h"

#include "AbilitySystemComponent.h"
#include "GAS/ARPGFoeGameplayAbility.h"

void UARPGDataAsset_FoeInit::GrantDefaultAbilities(UAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel) const
{
	check(AbilitySystemComponent);
	
	GrantAbilitiesFromArray(ActivateOnGivenAbilities, AbilitySystemComponent, ApplyLevel);
	GrantAbilitiesFromArray(ReactiveAbilities, AbilitySystemComponent, ApplyLevel);

	if (EnemyCombatAbilities.IsEmpty())
	{
		return;
	}
	
	for (const TSubclassOf<UARPGGameplayAbility> AbilityClass : EnemyCombatAbilities)
	{
		if(!AbilityClass) continue;

		FGameplayAbilitySpec AbilitySpec(AbilityClass);
		AbilitySpec.SourceObject = AbilitySystemComponent->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void UARPGDataAsset_FoeInit::GrantAbilitiesFromArray(TArray<TSubclassOf<UARPGGameplayAbility>> Abilities,
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
