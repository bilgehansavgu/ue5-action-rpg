// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ARPGFoeWeapon.h"
#include "GameplayAbilitySpecHandle.h"

#include "Components/BoxComponent.h"

AARPGFoeWeapon::AARPGFoeWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(Mesh);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());
	CollisionBox->SetBoxExtent(FVector(20.f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AARPGFoeWeapon::SetGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& SpecHandles)
{
	GrantedAbilitySpecHandles = SpecHandles;
}

