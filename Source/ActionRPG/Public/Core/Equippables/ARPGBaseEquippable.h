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
	// Sets default values for this actor's properties
	AARPGBaseEquippable();

	TObjectPtr<UPrimitiveComponent> GetItemMesh();
	
	UFUNCTION()
	void OnEquipped(FName SocketName);

	UFUNCTION()
	void OnUnequipped(FName SocketName);

	UFUNCTION()
	bool IsEquipped() const { return bIsEquipped; }

protected:

	UFUNCTION()
	void AttachToActor(FName SocketName);
	
	UFUNCTION()
	void SetIsEquipped(bool bIsEquipped);

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	bool bIsEquipped;
};
