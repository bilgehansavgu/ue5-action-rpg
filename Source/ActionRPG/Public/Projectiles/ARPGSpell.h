// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Projectiles/ARPGProjectileBase.h"
#include "GameFramework/Actor.h"
#include "ARPGSpell.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraComponent;

UCLASS()
class ACTIONRPG_API AARPGSpell : public AARPGProjectileBase
{
	GENERATED_BODY()
	
public:	
	AARPGSpell();

protected:
	
};
