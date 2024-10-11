// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ARPGBaseFoeWeapon.h"
#include "GameplayAbilitySpecHandle.h"

#include "Components/BoxComponent.h"

AARPGBaseFoeWeapon::AARPGBaseFoeWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(Mesh);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());
	CollisionBox->SetBoxExtent(FVector(20.f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AARPGBaseFoeWeapon::SetGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& SpecHandles)
{
	GrantedAbilitySpecHandles = SpecHandles;
}

