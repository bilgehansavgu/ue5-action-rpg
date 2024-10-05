// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ARPGAbilitySystemComponent.generated.h"

UCLASS()
class ACTIONRPG_API UARPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnAbilityInputPressed(const FGameplayTag& InputTag);

	UFUNCTION()
	void OnAbilityInputReleased(const FGameplayTag& InputTag);
};
