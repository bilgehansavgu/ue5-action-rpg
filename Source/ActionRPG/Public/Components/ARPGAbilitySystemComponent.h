// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ARPGAbilitySystemComponent.generated.h"

struct FARPGPlayerTaggedAbility;

UCLASS()
class ACTIONRPG_API UARPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnAbilityInputPressed(const FGameplayTag& InputTag);

	UFUNCTION()
	void OnAbilityInputReleased(const FGameplayTag& InputTag);

	UFUNCTION(BlueprintCallable, Category = "ARPG|Ability", meta = (ApplyLevel = "1"))
	void GiveWeaponAbilitiesToPlayer(TArray<FARPGPlayerTaggedAbility> WeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& GrantedAbilityHandles);

	UFUNCTION(BlueprintCallable, Category = "ARPG|Ability")
	void RemoveWeaponAbilitiesFromPlayer(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& GrantedAbilityHandles);
};
