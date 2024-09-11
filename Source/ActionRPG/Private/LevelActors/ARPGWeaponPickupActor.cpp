// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelActors/ARPGWeaponPickupActor.h"

#include "Characters/ARPGCharacter.h"
#include "Equippables/ARPGBaseEquippable.h"

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
		if (CharacterOwner->GetMainWeapon())
		{
			if (EquippableClass == CharacterOwner->GetMainWeapon()->GetClass())
			{
				return;
			}
		}

		CharacterOwner->PickUpWeapon(EquippableClass);
		
		//Destroy();
	}
}
