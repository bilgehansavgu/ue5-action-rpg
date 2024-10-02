// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Components/ARPGCombatComponent.h"
#include "ARPGGameplayAbility.generated.h"

class UARPGAbilitySystemComponent;

UENUM(BlueprintType)
enum class EARPGAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class ACTIONRPG_API UARPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:

	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface

	UFUNCTION(BlueprintPure, Category= "ARPG|Ability")
	UARPGCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category= "ARPG|Ability")
	UARPGAbilitySystemComponent* GetARPGAbilitySystemComponentFromActorInfo() const;

	UPROPERTY(EditDefaultsOnly, Category = "ARPG|Ability")
	EARPGAbilityActivationPolicy AbilityActivationPolicy = EARPGAbilityActivationPolicy::OnTriggered;
};
