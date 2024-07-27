// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/PickupActors/ARPGBasePickupActor.h"
#include "ARPGWeaponPickupActor.generated.h"


UCLASS()
class ACTIONRPG_API AARPGWeaponPickupActor : public AARPGBasePickupActor
{
	GENERATED_BODY()

public:

	AARPGWeaponPickupActor();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
