// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ARPGBTService_CheckAttack.generated.h"

UCLASS()
class ACTIONRPG_API UARPGBTService_CheckAttack : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "ARPG|AI")
	FBlackboardKeySelector ShouldAttackKey;

	UPROPERTY(EditAnywhere, Category = "ARPG|AI")
	FBlackboardKeySelector ShouldRunAwayKey;

	UPROPERTY(EditAnywhere, Category = "ARPG|AI")
	FBlackboardKeySelector ShouldChaseKey;
	
	UPROPERTY(EditAnywhere, Category = "ARPG|AI")
	float AttackMinRange;
	
	UPROPERTY(EditAnywhere, Category = "ARPG|AI")
	float AttackMaxRange;

	UPROPERTY(EditAnywhere, Category = "ARPG|AI")
	float RunAwayRange;
};
