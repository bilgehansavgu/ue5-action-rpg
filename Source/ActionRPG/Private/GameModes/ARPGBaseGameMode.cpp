// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/ARPGBaseGameMode.h"

#include "Characters/ARPGCharacter.h"
#include "Components/ARPGAISpawnerComponent.h"

class AARPGAICharacter;

AARPGBaseGameMode::AARPGBaseGameMode()
{
	AISpawnerComponent = CreateDefaultSubobject<UARPGAISpawnerComponent>(TEXT("AISpawnerComponent"));
}

void AARPGBaseGameMode::StartPlay()
{
	Super::StartPlay();

	if(ensure(AISpawnerComponent))
	{
		AISpawnerComponent->StartSpawning();
	}
}

void AARPGBaseGameMode::OnActorKilled(AActor* KilledActor, AActor* KillerActor)
{
	if(AARPGCharacter* KilledCharacter = Cast<AARPGCharacter>(KilledActor))
	{
		if (AController* KilledCharacterController = KilledCharacter->GetController())
		{
			FTimerHandle RespawnTimerHandle;
			FTimerDelegate RespawnTimerDelegate;
			
			RespawnTimerDelegate.BindUObject(this, &AARPGBaseGameMode::RespawnPlayer, KilledCharacterController);
			
			GetWorldTimerManager().SetTimer(RespawnTimerHandle, RespawnTimerDelegate, RespawnTimerInterval, false);
		}
	}
}

void AARPGBaseGameMode::RespawnPlayer(AController* Controller)
{
	if (IsValid(Controller))
	{
		if (AActor* OldPawn = Controller->GetPawn(); IsValid(OldPawn))
		{
			OldPawn->Destroy();
		}
		
		Controller->UnPossess();
		RestartPlayer(Controller);
	}
}