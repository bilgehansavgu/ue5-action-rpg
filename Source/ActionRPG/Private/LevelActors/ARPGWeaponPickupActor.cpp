// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelActors/ARPGWeaponPickupActor.h"

#include "Characters/ARPGCharacter.h"
#include "Components/ARPGInventoryComponent.h"
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
		if (CharacterOwner->GetInventoryComponent()->GetMainWeapon())
		{
			if (EquippableClass == CharacterOwner->GetInventoryComponent()->GetMainWeapon()->GetClass())
			{
				return;
			}
		}

		CharacterOwner->GetInventoryComponent()->PickUpWeapon(CharacterOwner, EquippableClass);
		
		//Destroy();
	}
}
