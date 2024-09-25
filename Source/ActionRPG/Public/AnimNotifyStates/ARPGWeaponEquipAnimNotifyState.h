// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ARPGWeaponEquipAnimNotifyState.generated.h"

UCLASS()
class ACTIONRPG_API UARPGWeaponEquipAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

protected:

	UPROPERTY()
	TObjectPtr<AActor> Owner;
};
