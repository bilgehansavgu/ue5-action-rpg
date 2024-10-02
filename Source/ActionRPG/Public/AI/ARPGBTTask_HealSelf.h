// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ARPGBTTask_HealSelf.generated.h"

UCLASS()
class ACTIONRPG_API UARPGBTTask_HealSelf : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "ARPG|AI")
	FBlackboardKeySelector LastHealTimeKey;
};
