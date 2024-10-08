// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/ARPGStructTypes.h"

#include "GAS/ARPGPlayerGameplayAbility.h"


bool FARPGPlayerTaggedAbility::IsValid() const
{
	return InputTag.IsValid() && Ability;
}