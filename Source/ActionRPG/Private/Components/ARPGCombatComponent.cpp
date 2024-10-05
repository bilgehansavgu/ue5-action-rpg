// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGCombatComponent.h"

#include "ActionRPG/ARPGDebugHelper.h"
#include "Weapons/ARPGBaseBeardWeapon.h"

void UARPGCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTag, AARPGBaseBeardWeapon* Weapon, bool bRegisterAsEquippedWeapon)
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

AARPGBaseBeardWeapon* UARPGCombatComponent::GetCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	if (CarriedWeaponMap.Contains(WeaponTag))
	{
		if (AARPGBaseBeardWeapon* const* FoundWeapon = CarriedWeaponMap.Find(WeaponTag))
		{
			return *FoundWeapon;
		}
	}
	return nullptr;
}


AARPGBaseBeardWeapon* UARPGCombatComponent::GetEquippedWeapon() const
{
	if (!EquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	return GetCarriedWeaponByTag(EquippedWeaponTag);
}
