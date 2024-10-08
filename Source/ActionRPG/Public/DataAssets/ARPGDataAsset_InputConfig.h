// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ARPGDataAsset_InputConfig.generated.h"


struct FARPGTaggedInputAction;
class UInputMappingContext;
class UInputAction;


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
	TArray<FARPGTaggedInputAction> TaggedInputActions;

	TObjectPtr<UInputAction> FindNativeInputActionByTag(const FGameplayTag& Tag) const;
};
