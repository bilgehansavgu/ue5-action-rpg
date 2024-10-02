// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGBaseAnimInstance.h"
#include "ARPGCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AARPGCharacterBeard;

UCLASS()
class ACTIONRPG_API UARPGCharacterAnimInstance : public UARPGBaseAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override; // works on the worker thread instead of game thread so it is good for optimization

protected:

	UPROPERTY()
	TObjectPtr<AARPGCharacterBeard> OwnerCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwnerMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ARPG|LocomotionData")
	float GroundSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ARPG|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ARPG|LocomotionData")
	bool bShouldEnterRelaxState;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ARPG|LocomotionData")
	float EnterRelaxStateThreshold{5.f};
	
	float IdleElapsedTime;
	

};
