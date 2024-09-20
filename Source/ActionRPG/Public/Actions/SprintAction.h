// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ARPGAction.h"
#include "SprintAction.generated.h"

UCLASS()
class ACTIONRPG_API USprintAction : public UARPGAction
{
	GENERATED_BODY()

public:
	
	virtual void StartAction_Implementation(UARPGAction* Action, AActor* Instigator) override;

	virtual void StopAction_Implementation(UARPGAction* Action, AActor* Instigator) override;

protected:
	USprintAction();
};
