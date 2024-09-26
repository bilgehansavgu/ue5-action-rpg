// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGAISpawnerComponent.h"

#include "EngineUtils.h"
#include "Characters/ARPGAICharacter.h"
#include "Components/ARPGAttributeComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

class UARPGAttributeComponent;
class AARPGAICharacter;

static TAutoConsoleVariable<bool> CVarSpawnAI(TEXT("arpg.SpawnAI"), true, TEXT("Enable AI spawning"), ECVF_Cheat);


void UARPGAISpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UARPGAISpawnerComponent::StartSpawning()
{
	GetOwner()->GetWorldTimerManager().SetTimer(SpawnAITimerHandle, this, &UARPGAISpawnerComponent::SpawnAITimerElapsed, AISpawnTimerInterval, true);
}


void UARPGAISpawnerComponent::SpawnAITimerElapsed()
{
	if (!CVarSpawnAI.GetValueOnGameThread())
	{
		return;
	}
	
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

void UARPGAISpawnerComponent::OnSpawnAIQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Type::Success)
	{
		UE_LOG(LogTemp, Error, TEXT("Spawn AI query failed!"));
		return;
	}
	
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if(Locations.IsValidIndex(0))
	{
		if(ensure(AICharacterClass))
		{
			GetWorld()->SpawnActor<AActor>(AICharacterClass, Locations[0], FRotator::ZeroRotator);
		}
	}
}

