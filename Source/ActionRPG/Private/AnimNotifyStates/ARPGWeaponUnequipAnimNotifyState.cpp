// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyStates/ARPGWeaponUnequipAnimNotifyState.h"

#include "Characters/ARPGCharacter.h"
#include "Components/ARPGInventoryComponent.h"

void UARPGWeaponUnequipAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp,
                                                    UAnimSequenceBase* Animation, float TotalDuration,
                                                    const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		if (Owner = Cast<AARPGCharacter>(MeshComp->GetOwner()))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("xxx")));
			Cast<AARPGCharacter>(Owner)->GetInventoryComponent()->PutBackWeapon();
		}
	}
}
