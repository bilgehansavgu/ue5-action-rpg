// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ARPGAttributeSet.h"

UARPGAttributeSet::UARPGAttributeSet()
{
	//showdebug abilitysystem
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(0.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefencePower(1.f);
}
