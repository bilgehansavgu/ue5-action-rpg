// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGActionComponent.h"
#include "Actions/ARPGAction.h"


void UARPGActionComponent::BeginPlay()
{
	Super::BeginPlay();

    for (const TSubclassOf<UARPGAction> Action : DefaultActions)
    {
        AddAction(Action);
    }
}

void UARPGActionComponent::AddAction(TSubclassOf<UARPGAction> ActionClass)
{
    if (!ensure(ActionClass))
    {
        return;
    }
    
    if (UARPGAction* NewAction = NewObject<UARPGAction>(this, ActionClass))
    {
        Actions.Add(NewAction);
    }
}

bool UARPGActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
    for (UARPGAction* Action : Actions)
    {
        if (Action && Action->GetActionName() == ActionName)
        {
            Action->StartAction(Action, Instigator);
            return true;
        }
    }
    return false;
}

bool UARPGActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
    for (UARPGAction* Action : Actions)
    {
        if (Action && Action->GetActionName() == ActionName)
        {
            Action->StopAction(Action, Instigator);
            return true;
        }
    }
    return false;
}