
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARPGInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API UARPGInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UARPGInventoryComponent();

protected:

	UPROPERTY(EditAnywhere)
	uint16 Coin_Amount{0};

	// add code here a slot for main weapon

public:
	// void AddItem(AARPGInventoryItem* Item);
	// void RemoveItem(AARPGInventoryItem* Item);
	// AARPGInventoryItem* GetItem(int32 Index) const;
	// int32 GetInventorySize() const;
	

};
