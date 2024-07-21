// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARPGInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API UARPGInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UARPGInteractionComponent();
	
	void Interact();

protected:

	UPROPERTY(EditAnywhere)
	uint16 EndDistance{1000};

	UPROPERTY(EditAnywhere)
	float ShapeRadius{30.f};
		
};
