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
	void RegisterSpawnedWeapon(FGameplayTag WeaponTag,AARPGPlayerWeapon* Weapon,bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGPlayerWeapon* GetCarriedWeaponByTag(FGameplayTag WeaponTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGPlayerWeapon* GetEquippedWeapon() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ARPG|Combat")
	FGameplayTag EquippedWeaponTag;
	
private:
	TMap<FGameplayTag,AARPGPlayerWeapon*> CarriedWeaponMap;
	
};
