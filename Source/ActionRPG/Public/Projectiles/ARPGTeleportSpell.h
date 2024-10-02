// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/ARPGProjectileBase.h"
#include "ARPGTeleportSpell.generated.h"

UCLASS()
class ACTIONRPG_API AARPGTeleportSpell : public AARPGProjectileBase
{
	GENERATED_BODY()

	AARPGTeleportSpell();

protected:

	virtual void BeginPlay() override;

	virtual void Explode_Implementation() override;

	void TeleportInstigator();
	
	UPROPERTY(EditDefaultsOnly, Category = "ARPG|Teleport")
	float TeleportDelay = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "ARPG|Teleport")
	float DetonateDelay = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "ARPG|Effects")
	TObjectPtr<UNiagaraSystem> DashEffect;

	FTimerHandle TimerHandle_DelayedDetonate;
};
