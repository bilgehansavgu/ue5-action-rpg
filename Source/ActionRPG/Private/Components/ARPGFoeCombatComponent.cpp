// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGFoeCombatComponent.h"

#include "ActionRPG/ARPGDebugHelper.h"
#include "Weapons/ARPGFoeWeapon.h"

void UARPGFoeCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTag, AARPGFoeWeapon* Weapon, bool bRegisterAsEquippedWeapon)
{
	checkf(!CarriedWeaponMap.Contains(WeaponTag), TEXT("A named named %s has already been added as carried weapon"),
		   *WeaponTag.ToString());
	check(Weapon);
	
	CarriedWeaponMap.Emplace(WeaponTag, Weapon);
	if (bRegisterAsEquippedWeapon)
	{
		EquippedWeaponTag = WeaponTag;
	}
	
	const FString WeaponString = FString::Printf(
		TEXT("A weapon named: %s has been registered using the tag %s"), *Weapon->GetName(), *WeaponTag.ToString());
	Debug::Print(WeaponString);
}

AARPGFoeWeapon* UARPGFoeCombatComponent::GetCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	if (CarriedWeaponMap.Contains(WeaponTag))
	{
		if (AARPGFoeWeapon* const* FoundWeapon = CarriedWeaponMap.Find(WeaponTag))
		{
			return *FoundWeapon;
		}
	}
	return nullptr;
}


AARPGFoeWeapon* UARPGFoeCombatComponent::GetEquippedWeapon() const
{
	if (!EquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	return GetCarriedWeaponByTag(EquippedWeaponTag);
}