// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ARPGActionBase.h"
#include "ARPGSprintAction.generated.h"

UCLASS()
class ACTIONRPG_API UARPGSprintAction : public UARPGActionBase
{
	GENERATED_BODY()

public:
	
	virtual void StartAction_Implementation(UARPGActionBase* Action, AActor* Instigator) override;

	virtual void StopAction_Implementation(UARPGActionBase* Action, AActor* Instigator) override;

protected:
	UARPGSprintAction();
};
