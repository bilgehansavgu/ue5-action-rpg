// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyStates/ARPGThoughSwordEquip.h"

#include "Core/Characters/ARPGCharacter.h"

void UARPGThoughSwordEquip::NotifyBegin(USkeletalMeshComponent* MeshComp,
                                        UAnimSequenceBase* Animation, float TotalDuration,
                                        const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		if (Owner = Cast<AARPGCharacter>(MeshComp->GetOwner()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("xxx")));
			Cast<AARPGCharacter>(Owner)->DrawWeapon();
		}
	}
}
