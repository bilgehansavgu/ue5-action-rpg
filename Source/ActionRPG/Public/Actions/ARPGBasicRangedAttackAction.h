// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ARPGActionBase.h"
#include "ARPGBasicRangedAttackAction.generated.h"

class AARPGProjectileBase;

UCLASS()
class ACTIONRPG_API UARPGBasicRangedAttackAction : public UARPGActionBase
{
	GENERATED_BODY()

public:
	UARPGBasicRangedAttackAction();
	
	virtual void StartAction_Implementation(UARPGActionBase* Action, AActor* Instigator) override;

	virtual void StopAction_Implementation(UARPGActionBase* Action, AActor* Instigator) override;

	UFUNCTION()
	void SpawnProjectile(ACharacter* InstigatorCharacter);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|Socket")
	FName RightHandSocketName{"ik_hand_rSocket"};

	UPROPERTY(EditAnywhere, Category = "ARPG|Projectile")
	TSubclassOf<AARPGProjectileBase> BasicRangedAttackClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|Projectile")
	float ProjectileTraceEndDistance{5000.f};
	
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|Projectile")
	float ProjectileTraceRadius{20.f};
};
