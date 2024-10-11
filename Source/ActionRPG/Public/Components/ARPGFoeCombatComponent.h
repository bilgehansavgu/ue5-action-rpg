// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGCombatComponent.h"
#include "GameplayTagContainer.h"
#include "ARPGFoeCombatComponent.generated.h"

class AARPGFoeWeapon;
struct FGameplayTag;

UCLASS()
class ACTIONRPG_API UARPGFoeCombatComponent : public UARPGCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	void RegisterSpawnedWeapon(FGameplayTag WeaponTag,AARPGFoeWeapon* Weapon,bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGFoeWeapon* GetCarriedWeaponByTag(FGameplayTag WeaponTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGFoeWeapon* GetEquippedWeapon() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ARPG|Combat")
	FGameplayTag EquippedWeaponTag;
	
private:
	TMap<FGameplayTag,AARPGFoeWeapon*> CarriedWeaponMap;
	
};
