// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGBaseAnimInstance.h"
#include "ARPGBeardLinkedAnimLayer.generated.h"

class UARPGBeardAnimInstance;

UCLASS()
class ACTIONRPG_API UARPGBeardLinkedAnimLayer : public UARPGBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UARPGBeardAnimInstance* GetCharacterAnimInstance() const;
};
