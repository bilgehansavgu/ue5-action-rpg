// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Projectiles/ARPGProjectileBase.h"
#include "ARPGAreaOfEffectSpell.generated.h"

UCLASS()
class ACTIONRPG_API AARPGAreaOfEffectSpell : public AARPGProjectileBase
{
	GENERATED_BODY()

	AARPGAreaOfEffectSpell();

protected:

	virtual void Explode_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(EditDefaultsOnly)
	float Radius{500.f};
};
