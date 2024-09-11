// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ARPG_BTServiceCheckAttack.generated.h"

UCLASS()
class ACTIONRPG_API UARPG_BTServiceCheckAttack : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackRangeKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	float AttackRange;
};
