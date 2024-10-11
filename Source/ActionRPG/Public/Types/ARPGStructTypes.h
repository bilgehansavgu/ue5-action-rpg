// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameplayTagContainer.h"

#include "ARPGStructTypes.generated.h"

class UARPGFoeGameplayAbility;
class UInputMappingContext;
class UARPGPlayerGameplayAbility;
class UInputAction;
class UARPGBeardLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FARPGPlayerTaggedAbility
{
	GENERATED_BODY()
	
	// The Categories keyword restricts the tags to those starting with "Input".
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories = "Input")) 
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UARPGPlayerGameplayAbility> Ability;
	
	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FARPGFoeTaggedAbility
{
	GENERATED_BODY()
	
	// The Categories keyword restricts the tags to those starting with "Input".
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories = "Input")) 
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UARPGFoeGameplayAbility> Ability;
	
	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FARPGTaggedInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Input")) // Categories meta tag is to only allow tags starting with "Input"
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;

	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction;
	}
};

USTRUCT(BlueprintType)
struct FARPGPlayerWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UARPGBeardLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty = "InputTag"))
	TArray<FARPGPlayerTaggedAbility> DefaultAbilities;
};

USTRUCT(BlueprintType)
struct FARPGFoeWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UARPGBeardLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FARPGFoeTaggedAbility> DefaultAbilities;
};