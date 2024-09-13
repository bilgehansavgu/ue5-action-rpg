// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ARPGGameMode.generated.h"

namespace EEnvQueryStatus
{
	enum Type : int;
}

class UEnvQuery;

UCLASS()
class ACTIONRPG_API AARPGGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AARPGGameMode();

	virtual void StartPlay() override;

protected:
	UFUNCTION()
	void SpawnAITimerElapsed();
	
	UFUNCTION()
	void OnSpawnAIQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float AISpawnTimerInterval{2.f};

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TObjectPtr<UEnvQuery> SpawnAIEnvQuery;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AActor> AIClass;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	int32 MaxAICount;
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	TObjectPtr<UCurveFloat> MaxAICountCurve;
	
	FTimerHandle SpawnAITimerHandle;
};
