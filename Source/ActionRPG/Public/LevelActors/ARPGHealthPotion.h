// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ARPGInteractableInterface.h"
#include "GameFramework/Actor.h"
#include "ARPGHealthPotion.generated.h"

UCLASS()
class ACTIONRPG_API AARPGHealthPotion : public AActor, public IARPGInteractableInterface
{
	GENERATED_BODY()
	
public:	

	AARPGHealthPotion();

	UFUNCTION()
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:

	void EnablePotion();
};
