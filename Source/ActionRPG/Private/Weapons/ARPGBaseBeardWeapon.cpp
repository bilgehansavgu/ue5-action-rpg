// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ARPGBaseBeardWeapon.h"

#include "Components/BoxComponent.h"


AARPGBaseBeardWeapon::AARPGBaseBeardWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(Mesh);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());
	CollisionBox->SetBoxExtent(FVector(20.f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AARPGBaseBeardWeapon::SetGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& SpecHandles)
{
	GrantedAbilitySpecHandles = SpecHandles;
}


