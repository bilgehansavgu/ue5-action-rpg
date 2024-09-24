// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ARPGGameMode.generated.h"

class UARPGAISpawnerComponent;

UCLASS()
class ACTIONRPG_API AARPGGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AARPGGameMode();

	virtual void StartPlay() override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UARPGAISpawnerComponent> AISpawnerComponent;
};
