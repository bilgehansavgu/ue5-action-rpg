// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActors/ARPGWeaponPickupActor.h"

#include "Core/Characters/ARPGCharacter.h"
#include "Core/Equippables/ARPGBaseEquippable.h"

AARPGWeaponPickupActor::AARPGWeaponPickupActor()
{

}

void AARPGWeaponPickupActor::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!EquippableClass || !InstigatorPawn)
	{
		return;
	}
	
	if (AARPGCharacter* CharacterOwner = Cast<AARPGCharacter>(InstigatorPawn))
	{
		CharacterOwner->PickUpWeapon(EquippableClass);
		
		Destroy();
	}
}
