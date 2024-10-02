// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ARPGBTService_CheckHealth.generated.h"

UCLASS()
class ACTIONRPG_API UARPGBTService_CheckHealth : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "ARPG|AI")
	FBlackboardKeySelector ShouldHideAndHealKey;

	UPROPERTY(EditAnywhere, Category = "ARPG|AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float LowHealthThreshold{0.3f};
};
