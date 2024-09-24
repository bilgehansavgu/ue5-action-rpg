// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/ARPGGameMode.h"

#include "Components/ARPGAISpawnerComponent.h"

class AARPGAICharacter;

AARPGGameMode::AARPGGameMode()
{
	AISpawnerComponent = CreateDefaultSubobject<UARPGAISpawnerComponent>(TEXT("AISpawnerComponent"));
}

void AARPGGameMode::StartPlay()
{
	Super::StartPlay();

	if(ensure(AISpawnerComponent))
	{
		AISpawnerComponent->StartSpawning();
	}
}


