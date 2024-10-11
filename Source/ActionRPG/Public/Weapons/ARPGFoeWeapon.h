// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGWeapon.h"
#include "GameFramework/Actor.h"
#include "Types/ARPGStructTypes.h"
#include "ARPGFoeWeapon.generated.h"

class UBoxComponent;
struct FGameplayAbilitySpecHandle;

UCLASS()
class ACTIONRPG_API AARPGFoeWeapon : public AARPGWeapon
{
	GENERATED_BODY()
	
public:	
	AARPGFoeWeapon();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ARPG|WeaponData")
	FARPGFoeWeaponData FoeWeaponData;

};
