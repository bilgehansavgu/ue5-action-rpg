// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ARPGCombatComponentInterface.generated.h"

class UARPGCombatComponent;
UINTERFACE(MinimalAPI)
class UARPGCombatComponentInterface : public UInterface
{
	GENERATED_BODY()
};

class ACTIONRPG_API IARPGCombatComponentInterface
{
	GENERATED_BODY()

public:

	virtual UARPGCombatComponent* GetPawnCombatComponent() const = 0;
};
