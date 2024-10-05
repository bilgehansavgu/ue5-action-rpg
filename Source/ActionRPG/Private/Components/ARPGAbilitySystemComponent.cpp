// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGAbilitySystemComponent.h"

void UARPGAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UARPGAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
}
