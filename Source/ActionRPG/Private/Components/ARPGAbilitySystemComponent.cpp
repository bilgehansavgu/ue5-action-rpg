// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGAbilitySystemComponent.h"


#include "GAS/ARPGPlayerGameplayAbility.h"
#include "Types/ARPGStructTypes.h"

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

void UARPGAbilitySystemComponent::GiveWeaponAbilitiesToPlayer(TArray<FARPGPlayerTaggedAbility> WeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& GrantedAbilityHandles)
{
	if (WeaponAbilities.IsEmpty())
	{
		return;
	}

	for (const FARPGPlayerTaggedAbility& TaggedAbility : WeaponAbilities)
	{
		if (!TaggedAbility.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(TaggedAbility.Ability);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(TaggedAbility.InputTag);

		GrantedAbilityHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UARPGAbilitySystemComponent::RemoveWeaponAbilitiesFromPlayer(TArray<FGameplayAbilitySpecHandle>& GrantedAbilityHandles)
{
	if (GrantedAbilityHandles.IsEmpty())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : GrantedAbilityHandles)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}

	GrantedAbilityHandles.Empty();

	if (GrantedAbilityHandles.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("All weapon abilities have been removed from the player."));
	}
}
