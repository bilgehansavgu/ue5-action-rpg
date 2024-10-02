// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ARPGDataAsset_InputConfig.generated.h"


class UInputMappingContext;
class UInputAction;

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


UCLASS()
class ACTIONRPG_API UARPGDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditDefaultsOnly, meta = (TitleProperty = "InputTag"))
	TArray<FARPGTaggedInputAction> NativeTaggedInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FARPGTaggedInputAction> AbilityTaggedInputActions;

	TObjectPtr<UInputAction> FindNativeInputActionByTag(const FGameplayTag& Tag) const;
};
