// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayTags/APRGGameplayTags.h"

namespace ARPGGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Input_Move,"Input.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Look,"Input.Look");
	UE_DEFINE_GAMEPLAY_TAG(Input_EquipWeapon,"Input.EquipWeapon");
	UE_DEFINE_GAMEPLAY_TAG(Input_UnequipWeapon,"Input.UnequipWeapon");

	/** Player Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Axe,"Player.Weapon.Axe");
}
