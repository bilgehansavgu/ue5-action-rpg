// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGWeapon.h"
#include "GameFramework/Actor.h"
#include "Types/ARPGStructTypes.h"
#include "ARPGPlayerWeapon.generated.h"

struct FARPGPlayerWeaponData;
class UBoxComponent;

UCLASS()
class ACTIONRPG_API AARPGPlayerWeapon : public AARPGWeapon
{
	GENERATED_BODY()
	
public:	
	AARPGPlayerWeapon();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ARPG|WeaponData")
	FARPGPlayerWeaponData PlayerWeaponData;

};
