// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/ARPGGameMode.h"

#include "EngineUtils.h"
#include "Characters/ARPGAICharacter.h"
#include "Components/ARPGAttributeComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

class AARPGAICharacter;

AARPGGameMode::AARPGGameMode()
{
}

void AARPGGameMode::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(SpawnAITimerHandle, this, &AARPGGameMode::SpawnAITimerElapsed, AISpawnTimerInterval, true);
}

void AARPGGameMode::SpawnAITimerElapsed()
{
	if(!ensure(SpawnAIEnvQuery))
	{
		UE_LOG(LogTemp, Error, TEXT("invalid SpawnAIEnvQuery aborting SpawnAITimerElapsed()"));
		return;
	}

	if(!ensure(MaxAICountCurve))
	{
		UE_LOG(LogTemp, Error, TEXT("invalid MaxAICountCurve aborting SpawnAITimerElapsed()"));
		return;
	}

	int32 AliveAICount = 0;
	for(TActorIterator<AARPGAICharacter> It(GetWorld()); It; ++It)
	{
		if (AARPGAICharacter* AICharacter = *It)
		{
			UARPGAttributeComponent* AttributeComponent = Cast<UARPGAttributeComponent>(AICharacter->FindComponentByClass<UARPGAttributeComponent>());
			if (AttributeComponent && AttributeComponent->IsAlive())
			{
				AliveAICount++;		
			}
		}
	}

	MaxAICount = MaxAICountCurve->GetFloatValue(GetWorld()->GetTimeSeconds());
	if (AliveAICount == MaxAICount)
	{
		UE_LOG(LogTemp, Error, TEXT("Max AI count reached!"));
		return;
	}
		
	if(auto UEnvQueryInstanceBlueprintWrapper = UEnvQueryManager::RunEQSQuery(this, SpawnAIEnvQuery, this, EEnvQueryRunMode::Type::RandomBest5Pct, nullptr))
	{
		UEnvQueryInstanceBlueprintWrapper->GetOnQueryFinishedEvent().AddUniqueDynamic(this, &ThisClass::OnSpawnAIQueryFinished);
	}
}

void AARPGGameMode::OnSpawnAIQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Type::Success)
	{
		UE_LOG(LogTemp, Error, TEXT("Spawn AI query failed!"));
		return;
	}
	
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if(Locations.IsValidIndex(0))
	{
		if(ensure(AIClass))
		{
			GetWorld()->SpawnActor<AActor>(AIClass, Locations[0], FRotator::ZeroRotator);
		}
	}
}
