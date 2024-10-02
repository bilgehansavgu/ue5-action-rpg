// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ARPGBTTask_RangedAttack.generated.h"

class AARPGProjectileBase;

UCLASS()
class ACTIONRPG_API UARPGBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "ARPG|AI")
	TSubclassOf<AARPGProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "ARPG|AI")
	FName ProjectileSpawnSocketName = "Muzzle_Front";
};
