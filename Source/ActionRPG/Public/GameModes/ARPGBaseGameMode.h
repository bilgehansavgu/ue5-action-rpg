// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ARPGBaseGameMode.generated.h"

class UARPGAISpawnerComponent;

UCLASS()
class ACTIONRPG_API AARPGBaseGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AARPGBaseGameMode();

	virtual void StartPlay() override;

	virtual void OnActorKilled(AActor* KilledActor, AActor* KillerActor);

	UFUNCTION()
	void RespawnPlayer(AController* Controller);

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UARPGAISpawnerComponent> AISpawnerComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameMode")
	float RespawnTimerInterval{5.f};
};
