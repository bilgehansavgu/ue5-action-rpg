// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGCombatComponent.h"
#include "Weapons/ARPGWeapon.h"
#include "ActionRPG/ARPGDebugHelper.h"
#include "Components/BoxComponent.h"

class AARPGFoeWeapon;

void UARPGCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTag, AARPGWeapon* Weapon, bool bRegisterAsEquippedWeapon)
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

AARPGWeapon* UARPGCombatComponent::GetCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	if (CarriedWeaponMap.Contains(WeaponTag))
	{
		if (AARPGWeapon* const* FoundWeapon = CarriedWeaponMap.Find(WeaponTag))
		{
			return *FoundWeapon;
		}
	}
	return nullptr;
}

void UARPGCombatComponent::ToggleWeaponCollision(bool bIsEnabled, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AARPGWeapon* EquippedWeapon = GetEquippedWeapon();

		check(EquippedWeapon);

		if (bIsEnabled)
		{
			EquippedWeapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			EquippedWeapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}


AARPGWeapon* UARPGCombatComponent::GetEquippedWeapon() const
{
	if (!EquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	return GetCarriedWeaponByTag(EquippedWeaponTag);
}
