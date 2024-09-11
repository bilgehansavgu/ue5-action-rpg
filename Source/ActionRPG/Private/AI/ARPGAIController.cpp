// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARPGAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AARPGAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	GetBlackboardComponent()->SetValueAsObject("TargetActor", PlayerPawn);
}
