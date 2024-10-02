// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "ARPGBTDecorator_HealCooldown.generated.h"

UCLASS()
class ACTIONRPG_API UARPGBTDecorator_HealCooldown : public UBTDecorator
{
	GENERATED_BODY()

public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = "ARPG|AI")
	float CooldownTime{60.f};

	UPROPERTY(EditAnywhere, Category = "ARPG|AI")
	FBlackboardKeySelector LastHealTimeKey;
};
