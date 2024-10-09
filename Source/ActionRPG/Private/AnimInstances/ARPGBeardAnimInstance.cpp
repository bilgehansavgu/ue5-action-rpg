// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ARPGBeardAnimInstance.h"

#include "Characters/ARPGCharacterBeard.h"
#include "GameFramework/CharacterMovementComponent.h"

void UARPGBeardAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<AARPGCharacterBeard>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UARPGBeardAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwnerCharacter || !OwnerMovementComponent)
	{
		return;
	}
	GroundSpeed = OwnerCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwnerMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
}
