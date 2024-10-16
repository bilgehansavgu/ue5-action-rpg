// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ARPGBaseAnimInstance.h"
#include "ARPGFoeAnimInstance.generated.h"

class UCharacterMovementComponent;
class AARPGCharacterFoe;

UCLASS()
class ACTIONRPG_API UARPGFoeAnimInstance : public UARPGBaseAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override; // works on the worker thread instead of game thread so it is good for optimization

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|References")
	TObjectPtr<AARPGCharacterFoe> OwnerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|References")
	TObjectPtr<UCharacterMovementComponent> OwnerMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ARPG|LocomotionData")
	float GroundSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ARPG|LocomotionData")
	bool bHasAcceleration;
};
