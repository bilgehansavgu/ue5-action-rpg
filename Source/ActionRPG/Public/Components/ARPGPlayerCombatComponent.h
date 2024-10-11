// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGCombatComponent.h"
#include "GameplayTagContainer.h"
#include "ARPGPlayerCombatComponent.generated.h"


class AARPGBaseBeardWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONRPG_API UARPGPlayerCombatComponent : public UARPGPawnComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	void RegisterSpawnedWeapon(FGameplayTag WeaponTag,AARPGBaseBeardWeapon* Weapon,bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGBaseBeardWeapon* GetCarriedWeaponByTag(FGameplayTag WeaponTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGBaseBeardWeapon* GetEquippedWeapon() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ARPG|Combat")
	FGameplayTag EquippedWeaponTag;
	
private:
	TMap<FGameplayTag,AARPGBaseBeardWeapon*> CarriedWeaponMap;
	
};
