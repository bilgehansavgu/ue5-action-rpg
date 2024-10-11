// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ARPGDataAsset_PlayerInit.generated.h"

struct FARPGPlayerTaggedAbility;
class UAbilitySystemComponent;
class UARPGGameplayAbility;
class UGameplayEffect;


UCLASS()
class ACTIONRPG_API UARPGDataAsset_PlayerInit : public UDataAsset
{
	GENERATED_BODY()

public:

	virtual void GrantDefaultAbilities(UAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel = 1) const;
	
protected:

	UFUNCTION()
	void GrantAbilitiesFromArray(TArray<TSubclassOf<UARPGGameplayAbility>> Abilities, UAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|InitData")
	TArray<TSubclassOf<UARPGGameplayAbility>> ActivateOnGivenAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|InitData")
	TArray<TSubclassOf<UARPGGameplayAbility>> ReactiveAbilities;

	// The TitleProperty keyword specifies which property to display as the title in the editor UI for elements of this array.
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|InitData", meta=(TitleProperty = "InputTag"))
	TArray<FARPGPlayerTaggedAbility> PlayerStartTaggedGameplayAbility;
	
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|InitData")
	TArray<TSubclassOf<UGameplayEffect>> InitGameplayEffects;
};
