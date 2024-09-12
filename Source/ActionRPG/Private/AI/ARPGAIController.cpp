// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARPGAIController.h"


void AARPGAIController::BeginPlay()
{
	Super::BeginPlay();
	if(ensure(BehaviorTree))
	{
		RunBehaviorTree(BehaviorTree);
	}
}
