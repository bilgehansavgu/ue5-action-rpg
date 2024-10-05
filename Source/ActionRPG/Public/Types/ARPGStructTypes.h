// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARPGStructTypes.generated.h"

class UARPGBeardLinkedAnimLayer;


USTRUCT(BlueprintType)
struct FARPGPlayerWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UARPGBeardLinkedAnimLayer> WeaponAnimLayerToLink;
};