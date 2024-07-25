// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Interfaces/ARPGInteractableInterface.h"
#include "GameFramework/Actor.h"
#include "ARPGBasePickupActor.generated.h"

class AARPGBaseEquippable;

UCLASS()
class ACTIONRPG_API AARPGBasePickupActor : public AActor, public IARPGInteractableInterface
{
	GENERATED_BODY()
	
public:	

	AARPGBasePickupActor();

	UFUNCTION()
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	UFUNCTION()
	void SetEquippableClass(TSubclassOf<AARPGBaseEquippable> Equippable);
	
protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AARPGBaseEquippable> EquippableClass;

};
