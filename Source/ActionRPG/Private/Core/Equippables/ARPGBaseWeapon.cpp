// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Equippables/ARPGBaseWeapon.h"

#include "GameFramework/Character.h"

FName AARPGBaseWeapon::GetEquippedSocketName() const
{
	return EquippedSocketName;
}

FName AARPGBaseWeapon::GetUnequippedSocketName() const
{
	return UnequippedSocketName;
}

UAnimMontage* AARPGBaseWeapon::GetDrawAnimationMontage() const
{
	return DrawAnimation;
}

UAnimMontage* AARPGBaseWeapon::GetDisarmAnimationMontage() const
{
	return DisarmAnimation;
}

void AARPGBaseWeapon::SetEquippedSocketName(FName SocketName)
{
	EquippedSocketName = SocketName;
}

void AARPGBaseWeapon::SetUnequippedSocketName(FName SocketName)
{
	UnequippedSocketName = SocketName;
}

void AARPGBaseWeapon::OnEquipped(AActor* Actor)
{
	if (ACharacter* CharacterOwner = Cast<ACharacter>(Actor))
	{
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(CharacterOwner->GetMesh(), AttachmentRules, EquippedSocketName);
	}
	SetIsEquipped(true);
}

void AARPGBaseWeapon::OnUnequipped(AActor* Actor)
{
	if (ACharacter* CharacterOwner = Cast<ACharacter>(Actor))
	{
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(CharacterOwner->GetMesh(), AttachmentRules, GetUnequippedSocketName());
	}
	SetIsEquipped(false);
}
