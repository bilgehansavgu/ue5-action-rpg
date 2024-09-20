// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ARPGAction.generated.h"

UCLASS(Blueprintable)
class ACTIONRPG_API UARPGAction : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(UARPGAction* Action, AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StopAction(UARPGAction* Action, AActor* Instigator);

	UFUNCTION(BlueprintPure, Category = "Action")
	FName GetActionName() const { return ActionName; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;
};
