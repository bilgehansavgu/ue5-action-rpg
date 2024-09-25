// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ARPGSprintAction.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/MovementComponent.h"


UARPGSprintAction::UARPGSprintAction()
{
	ActionName = "Sprint";
}

void UARPGSprintAction::StartAction_Implementation(UARPGActionBase* Action, AActor* Instigator)
{
	Super::StartAction_Implementation(Action, Instigator);

	if (!Instigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("Instigator is null in StartAction"));
		return;
	}

	if (UCharacterMovementComponent* MovementComponent = Instigator->FindComponentByClass<UCharacterMovementComponent>())
	{
		Instigator->GetComponentByClass<UCharacterMovementComponent>()->MaxWalkSpeed *= 2;
	}
}

void UARPGSprintAction::StopAction_Implementation(UARPGActionBase* Action, AActor* Instigator)
{
	Super::StopAction_Implementation(Action, Instigator);
	
	if (!Instigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("Instigator is null in StopAction"));
		return;
	}
	
	if (UCharacterMovementComponent* MovementComponent = Instigator->GetComponentByClass<UCharacterMovementComponent>())
	{
		MovementComponent->MaxWalkSpeed /= 2;
	}
}
