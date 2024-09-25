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
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName RightHandSocketName{"ik_hand_rSocket"};

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AARPGProjectileBase> BasicRangedAttackClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float ProjectileTraceEndDistance{5000.f};
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float ProjectileTraceRadius{20.f};
};
