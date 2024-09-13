// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGAICharacter.h"

#include "AI/ARPGAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ARPGAttributeComponent.h"
#include "Perception/PawnSensingComponent.h"

class AARPGAIController;

AARPGAICharacter::AARPGAICharacter()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	AttributeComponent = CreateDefaultSubobject<UARPGAttributeComponent>(TEXT("AttributeComponent"));
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

void AARPGAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AARPGAICharacter::OnSeePawn);
}

void AARPGAICharacter::OnSeePawn(APawn* Pawn)
{
	AARPGAIController* AIController = Cast<AARPGAIController>(GetController());
	if (AIController)
	{
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
		AIController->GetBlackboardComponent()->SetValueAsObject("TargetActor", Pawn);
		DrawDebugString(GetWorld(), GetActorLocation(), "I see you!", nullptr, FColor::Red, 2.0f);
	}

}

