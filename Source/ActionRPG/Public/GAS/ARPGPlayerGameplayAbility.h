// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/ARPGGameplayAbility.h"
#include "ARPGPlayerGameplayAbility.generated.h"


class UARPGPlayerCombatComponent;
class AARPGPlayerController;
class AARPGCharacterBeard;

UCLASS()
class ACTIONRPG_API UARPGPlayerGameplayAbility : public UARPGGameplayAbility
{
		GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	AARPGCharacterBeard* GetBeardCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	AARPGPlayerController* GetPlayerControllerFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	UARPGPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();
		
private:
	TWeakObjectPtr<AARPGCharacterBeard> CachedCharacter;
	TWeakObjectPtr<AARPGPlayerController> CachedPlayerController;
	
};
