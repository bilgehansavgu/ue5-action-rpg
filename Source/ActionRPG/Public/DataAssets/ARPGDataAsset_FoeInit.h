// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ARPGDataAsset_FoeInit.generated.h"

class UGameplayEffect;
class UARPGGameplayAbility;
class UAbilitySystemComponent;
class UARPGFoeGameplayAbility;

UCLASS()
class ACTIONRPG_API UARPGDataAsset_FoeInit : public UDataAsset
{
	GENERATED_BODY()

public:

	virtual void GrantDefaultAbilities(UAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel = 1) const;

private:

	UFUNCTION()
	void GrantAbilitiesFromArray(TArray<TSubclassOf<UARPGGameplayAbility>> Abilities, UAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|InitData")
	TArray<TSubclassOf<UARPGGameplayAbility>> ActivateOnGivenAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|InitData")
	TArray<TSubclassOf<UARPGGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "ARPG|InitData")
	TArray<TSubclassOf<UARPGFoeGameplayAbility>> EnemyCombatAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|InitData")
	TArray<TSubclassOf<UGameplayEffect>> InitGameplayEffects;
	
};
