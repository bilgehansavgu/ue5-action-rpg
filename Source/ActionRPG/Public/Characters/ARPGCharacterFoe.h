// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGCharacterFoe.generated.h"

class UARPGFoeCombatComponent;

UCLASS()
class ACTIONRPG_API AARPGCharacterFoe : public ACharacter
{
	GENERATED_BODY()

public:
	AARPGCharacterFoe();

	FORCEINLINE UARPGFoeCombatComponent* GetFoeCombatComponent() const { return FoeCombatComponent;}
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components")
	TObjectPtr<UARPGFoeCombatComponent> FoeCombatComponent;

};
