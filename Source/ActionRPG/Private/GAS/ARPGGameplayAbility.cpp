// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ARPGGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "Components/ARPGAbilitySystemComponent.h"

class UARPGCombatComponent;

void UARPGGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy	== EARPGAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, true);
		}
	}
}

void UARPGGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EARPGAbilityActivationPolicy::OnGiven)
	{
		ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
	}
}

UARPGCombatComponent* UARPGGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UARPGCombatComponent>();
}

UARPGAbilitySystemComponent* UARPGGameplayAbility::GetARPGAbilitySystemComponentFromActorInfo() const
{
	return Cast<UARPGAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}



