// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ARPGBeardLinkedAnimLayer.h"

#include "AnimInstances/ARPGBeardAnimInstance.h"

UARPGBeardAnimInstance* UARPGBeardLinkedAnimLayer::GetCharacterAnimInstance() const
{
	return Cast<UARPGBeardAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
