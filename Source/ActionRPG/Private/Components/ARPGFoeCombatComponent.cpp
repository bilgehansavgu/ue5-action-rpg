// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGFoeCombatComponent.h"

#include "Weapons/ARPGFoeWeapon.h"

AARPGFoeWeapon* UARPGFoeCombatComponent::GetFoeCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AARPGFoeWeapon>(GetCarriedWeaponByTag(InWeaponTag));
}

AARPGFoeWeapon* UARPGFoeCombatComponent::GetFoeEquippedWeapon(FGameplayTag InWeaponTag)
{
	return Cast<AARPGFoeWeapon>(GetEquippedWeapon());
}
