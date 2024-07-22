// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ARPGConsumableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UARPGConsumableInterface : public UInterface
{
	GENERATED_BODY()
};

class ACTIONRPG_API IARPGConsumableInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Consume(APawn* InstigatorPawn);
};
