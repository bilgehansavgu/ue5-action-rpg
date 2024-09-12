// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGAICharacter.generated.h"

UCLASS()
class ACTIONRPG_API AARPGAICharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AARPGAICharacter();

protected:

	virtual void BeginPlay() override;
};
