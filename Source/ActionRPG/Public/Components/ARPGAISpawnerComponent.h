// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARPGAISpawnerComponent.generated.h"


class UEnvQuery;

namespace EEnvQueryStatus
{
	enum Type : int;
}

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API UARPGAISpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void StartSpawning();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnAITimerElapsed();
	
	UFUNCTION()
	void OnSpawnAIQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float AISpawnTimerInterval{2.f};

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TObjectPtr<UEnvQuery> SpawnAIEnvQuery;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AActor> AICharacterClass;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	int32 MaxAICount{0};
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	TObjectPtr<UCurveFloat> MaxAICountCurve;
	
	FTimerHandle SpawnAITimerHandle;
};
