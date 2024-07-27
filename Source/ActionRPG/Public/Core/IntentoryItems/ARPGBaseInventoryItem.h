// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARPGBaseInventoryItem.generated.h"

UCLASS()
class ACTIONRPG_API AARPGBaseInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:
	
	AARPGBaseInventoryItem();

protected:

	UPROPERTY(EditAnywhere)
	FName ItemName;

	UPROPERTY(EditAnywhere)
	FName ItemDescription;

};
