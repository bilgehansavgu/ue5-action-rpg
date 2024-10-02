// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGActionBase.generated.h"

UCLASS(Blueprintable)
class ACTIONRPG_API UARPGActionBase : public UObject
{
	GENERATED_BODY()

public:

	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintNativeEvent, Category = "ARPG|Action")
	void StartAction(UARPGActionBase* Action, AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "ARPG|Action")
	void StopAction(UARPGActionBase* Action, AActor* Instigator);

	UFUNCTION(BlueprintPure, Category = "ARPG|Action")
	FName GetActionName() const { return ActionName; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|Action")
	FName ActionName;
};
