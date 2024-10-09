// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ARPGFoeAnimInstance.h"

#include "Characters/ARPGCharacterFoe.h"
#include "GameFramework/CharacterMovementComponent.h"

void UARPGFoeAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<AARPGCharacterFoe>(TryGetPawnOwner());
	 
	if (OwnerCharacter)
	{
		OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UARPGFoeAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwnerCharacter || !OwnerMovementComponent)
	{
		return;
	}

	GroundSpeed = OwnerCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwnerMovementComponent->GetCurrentAcceleration().SizeSquared2D()>0.f;
}