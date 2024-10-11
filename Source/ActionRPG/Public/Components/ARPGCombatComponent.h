// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ARPGPawnComponent.h"
#include "ARPGCombatComponent.generated.h"


class AARPGWeapon;

UCLASS()
class ACTIONRPG_API UARPGCombatComponent : public UARPGPawnComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	void RegisterSpawnedWeapon(FGameplayTag WeaponTag,AARPGWeapon* Weapon,bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGWeapon* GetCarriedWeaponByTag(FGameplayTag WeaponTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGWeapon* GetEquippedWeapon() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ARPG|Combat")
	FGameplayTag EquippedWeaponTag;
	
private:
	TMap<FGameplayTag,AARPGWeapon*> CarriedWeaponMap;
};
