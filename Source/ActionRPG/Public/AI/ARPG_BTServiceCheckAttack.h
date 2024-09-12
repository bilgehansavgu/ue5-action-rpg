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
	FBlackboardKeySelector ShouldAttackKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector ShouldRunAwayKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector ShouldChaseKey;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float AttackMinRange;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float AttackMaxRange;

	UPROPERTY(EditAnywhere, Category = "AI")
	float RunAwayRange;
};
