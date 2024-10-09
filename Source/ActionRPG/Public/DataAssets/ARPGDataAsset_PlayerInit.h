// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ARPGDataAsset_PlayerInit.generated.h"

struct FARPGPlayerTaggedAbility;
class UAbilitySystemComponent;
class UARPGGameplayAbility;


UCLASS()
class ACTIONRPG_API UARPGDataAsset_PlayerInit : public UDataAsset
{
	GENERATED_BODY()

public:

	virtual void GiveToAbilitySystemComponent(UAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel = 1) const;
	
protected:

	UFUNCTION()
	void GrantAbilities(TArray<TSubclassOf<UARPGGameplayAbility>> Abilities, UAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|StartData")
	TArray<TSubclassOf<UARPGGameplayAbility>> ActivateOnGivenAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|StartData")
	TArray<TSubclassOf<UARPGGameplayAbility>> ReactiveAbilities;

	// The TitleProperty keyword specifies which property to display as the title in the editor UI for elements of this array.
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|StartData", meta=(TitleProperty = "InputTag"))
	TArray<FARPGPlayerTaggedAbility> PlayerStartTaggedGameplayAbility;
};
