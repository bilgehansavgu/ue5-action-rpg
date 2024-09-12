// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGAICharacter.h"

#include "AI/ARPGAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/PawnSensingComponent.h"

class AARPGAIController;

AARPGAICharacter::AARPGAICharacter()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
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

