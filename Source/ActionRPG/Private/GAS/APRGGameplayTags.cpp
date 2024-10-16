// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/APRGGameplayTags.h"

namespace ARPGGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Input_Move,"Input.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Look,"Input.Look");
	UE_DEFINE_GAMEPLAY_TAG(Input_EquipWeapon,"Input.EquipWeapon");
	UE_DEFINE_GAMEPLAY_TAG(Input_UnequipWeapon,"Input.UnequipWeapon");
	UE_DEFINE_GAMEPLAY_TAG(Input_Attack_Light_Axe, "Input.Attack.Light.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Input_Attack_Heavy_Axe, "Input.Attack.Heavy.Axe");

	
	/** Player Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Axe,"Player.Weapon.Axe");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Axe, "Player.Event.Equip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Axe, "Player.Event.Unequip.Axe");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Axe, "Player.Ability.Equip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Axe, "Player.Ability.Unequip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Axe, "Player.Ability.Attack.Light.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Axe, "Player.Ability.Attack.Heavy.Axe");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher");


	/** Foe Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Foe_Weapon, "Foe.Weapon");
}
