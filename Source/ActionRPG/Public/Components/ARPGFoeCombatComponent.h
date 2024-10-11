// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGPawnComponent.h"
#include "GameplayTagContainer.h"
#include "ARPGFoeCombatComponent.generated.h"

class AARPGBaseFoeWeapon;
struct FGameplayTag;

UCLASS()
class ACTIONRPG_API UARPGFoeCombatComponent : public UARPGPawnComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	void RegisterSpawnedWeapon(FGameplayTag WeaponTag,AARPGBaseFoeWeapon* Weapon,bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGBaseFoeWeapon* GetCarriedWeaponByTag(FGameplayTag WeaponTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGBaseFoeWeapon* GetEquippedWeapon() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ARPG|Combat")
	FGameplayTag EquippedWeaponTag;
	
private:
	TMap<FGameplayTag,AARPGBaseFoeWeapon*> CarriedWeaponMap;
	
};
