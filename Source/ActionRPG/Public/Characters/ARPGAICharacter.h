// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGAICharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class ACTIONRPG_API AARPGAICharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AARPGAICharacter();

protected:

	UFUNCTION()
	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);
	
	UPROPERTY(VisibleAnywhere, Category="AI")
	TObjectPtr<UPawnSensingComponent> PawnSensingComponent;
};
