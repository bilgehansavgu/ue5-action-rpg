// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGCombatComponent.h"
#include "ARPGFoeCombatComponent.generated.h"

class AARPGFoeWeapon;
struct FGameplayTag;

UCLASS()
class ACTIONRPG_API UARPGFoeCombatComponent : public UARPGCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGFoeWeapon* GetFoeCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGFoeWeapon* GetFoeEquippedWeapon(FGameplayTag InWeaponTag);
	
};
