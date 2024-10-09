// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGCharacterFoe.h"

#include "Components/ARPGFoeCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AARPGCharacterFoe::AARPGCharacterFoe()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,180.f,0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;
	
	FoeCombatComponent = CreateDefaultSubobject<UARPGFoeCombatComponent>("FoeCombatComponent");
}

