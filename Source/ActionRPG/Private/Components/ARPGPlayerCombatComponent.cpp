// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGPlayerCombatComponent.h"

#include "Weapons/ARPGPlayerWeapon.h"

AARPGPlayerWeapon* UARPGPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AARPGPlayerWeapon>(GetCarriedWeaponByTag(InWeaponTag));
}

AARPGPlayerWeapon* UARPGPlayerCombatComponent::GetPlayerEquippedWeapon(FGameplayTag InWeaponTag)
{
	return Cast<AARPGPlayerWeapon>(GetEquippedWeapon());
}
