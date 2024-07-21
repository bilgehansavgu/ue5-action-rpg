// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/ARPGSpell.h"

#include "GameFramework/ProjectileMovementComponent.h"

AARPGSpell::AARPGSpell()
{
	MovementComponent->InitialSpeed = 3000.f;
}


