// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ARPGGameplayFunctionLibrary.generated.h"

UCLASS()
class ACTIONRPG_API UARPGGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION()
	static void ApplyDirectionalDamage(AActor* Instigator, AActor* Target, float Damage, float ImpulseMultiplier, const FHitResult& HitResult);

};
