// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "NativeGameplayTags.h"

namespace ARPGGameplayTags
{
	/** Input Tags **/
	ACTIONRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Move)
	ACTIONRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Look)
	ACTIONRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_EquipWeapon);
	ACTIONRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_UnequipWeapon);

	
	/** Player Tags **/
	ACTIONRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);
	
	ACTIONRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	ACTIONRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);

	ACTIONRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	ACTIONRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe);
	ACTIONRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	ACTIONRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);

	ACTIONRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);

	
	/** Foe Tags **/
	ACTIONRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Foe_Weapon);
}
