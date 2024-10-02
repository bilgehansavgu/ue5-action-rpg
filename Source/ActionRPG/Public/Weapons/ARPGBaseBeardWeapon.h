// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARPGBaseBeardWeapon.generated.h"

class UBoxComponent;

UCLASS()
class ACTIONRPG_API AARPGBaseBeardWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AARPGBaseBeardWeapon();
	
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return CollisionBox;}

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Weapons")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Weapons")
	TObjectPtr<UBoxComponent> CollisionBox;

};
