// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ARPGFoeCombatComponent.h"
#include "GAS/ARPGGameplayAbility.h"
#include "ARPGFoeGameplayAbility.generated.h"

class AARPGCharacterFoe;

UCLASS()
class ACTIONRPG_API UARPGFoeGameplayAbility : public UARPGGameplayAbility
{
	GENERATED_BODY()
		
public:
	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	AARPGCharacterFoe* GetFoeCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	UARPGFoeCombatComponent* GetFoeCombatComponentFromActorInfo();
	
protected:
	TWeakObjectPtr<AARPGCharacterFoe> CachedFoeCharacter;
};
