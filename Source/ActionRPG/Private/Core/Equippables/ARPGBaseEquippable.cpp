// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Equippables/ARPGBaseEquippable.h"

AARPGBaseEquippable::AARPGBaseEquippable() {
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");

	RootComponent = StaticMeshComponent;
}

TObjectPtr<UPrimitiveComponent> AARPGBaseEquippable::GetItemMesh()
{
		return IsValid(StaticMeshComponent) ? Cast<UPrimitiveComponent>(StaticMeshComponent) : Cast<UPrimitiveComponent>(SkeletalMeshComponent);
}

void AARPGBaseEquippable::SetIsEquipped(bool isEquipped)
{
	bIsEquipped = isEquipped;
}