// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ARPGBeardLinkedAnimLayer.h"

#include "AnimInstances/ARPGCharacterAnimInstance.h"

UARPGCharacterAnimInstance* UARPGBeardLinkedAnimLayer::GetCharacterAnimInstance() const
{
	return Cast<UARPGCharacterAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
