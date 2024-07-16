// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Equippables/ARPGBaseEquippable.h"

#include "GameFramework/Character.h"

// Sets default values
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

void AARPGBaseEquippable::AttachToActor(FName SocketName)
{
	if (ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner()))
	{
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(CharacterOwner->GetMesh(), AttachmentRules, SocketName);
	}
}

void AARPGBaseEquippable::OnEquipped(FName SocketName)
{
	AttachToActor(SocketName);
	SetIsEquipped(true);
}

void AARPGBaseEquippable::OnUnequipped(FName SocketName)
{
	AttachToActor(SocketName);
	SetIsEquipped(false);
}

void AARPGBaseEquippable::SetIsEquipped(bool isEquipped)
{
	bIsEquipped = isEquipped;
}