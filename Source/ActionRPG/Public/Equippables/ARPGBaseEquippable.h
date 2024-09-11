// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARPGBaseEquippable.generated.h"

UCLASS()
class ACTIONRPG_API AARPGBaseEquippable : public AActor
{
	GENERATED_BODY()
	
public:	

	AARPGBaseEquippable();

	TObjectPtr<UPrimitiveComponent> GetItemMesh();

	UFUNCTION()
	bool IsEquipped() const { return bIsEquipped; }

protected:
	
	UFUNCTION()
	void SetIsEquipped(bool bIsEquipped);

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	bool bIsEquipped;
};
