// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PickupActors/ARPGBasePickupActor.h"

AARPGBasePickupActor::AARPGBasePickupActor()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
}

void AARPGBasePickupActor::Interact_Implementation(APawn* InstigatorPawn)
{
	IARPGInteractableInterface::Interact_Implementation(InstigatorPawn);
}

void AARPGBasePickupActor::SetEquippableClass(TSubclassOf<AARPGBaseEquippable> Equippable)
{
	EquippableClass = Equippable;
}





