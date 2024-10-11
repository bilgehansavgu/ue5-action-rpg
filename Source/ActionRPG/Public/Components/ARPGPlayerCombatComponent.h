// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGCombatComponent.h"
#include "GameplayTagContainer.h"
#include "ARPGPlayerCombatComponent.generated.h"


class AARPGPlayerWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONRPG_API UARPGPlayerCombatComponent : public UARPGCombatComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGPlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGPlayerWeapon* GetPlayerEquippedWeapon(FGameplayTag InWeaponTag);

	
};
