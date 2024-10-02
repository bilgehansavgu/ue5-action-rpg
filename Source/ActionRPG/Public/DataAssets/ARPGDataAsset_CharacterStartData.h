// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ARPGDataAsset_CharacterStartData.generated.h"

class UAbilitySystemComponent;
class UARPGGameplayAbility;

USTRUCT(BlueprintType)
struct FARPGPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UARPGGameplayAbility> AbilityToGrant;
	
	bool IsValid() const;
};

UCLASS()
class ACTIONRPG_API UARPGDataAsset_CharacterStartData : public UDataAsset
{
	GENERATED_BODY()

public:

	virtual void GiveToAbilitySystemComponent(UAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel = 1) const;
	
protected:

	UFUNCTION()
	void GrantAbilities(TArray<TSubclassOf<UARPGGameplayAbility>> Abilities, UAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|StartUpData")
	TArray<TSubclassOf<UARPGGameplayAbility>> ActivateOnGivenAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|StartUpData")
	TArray<TSubclassOf<UARPGGameplayAbility>> ReactiveAbilities;

};
