// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGActionComponent.h"
#include "Actions/ARPGActionBase.h"


void UARPGActionComponent::BeginPlay()
{
	Super::BeginPlay();

    for (const TSubclassOf<UARPGActionBase> Action : DefaultActions)
    {
        AddAction(Action);
    }
}

void UARPGActionComponent::AddAction(TSubclassOf<UARPGActionBase> ActionClass)
{
    if (!ensure(ActionClass))
    {
        return;
    }
    
    if (UARPGActionBase* NewAction = NewObject<UARPGActionBase>(this, ActionClass))
    {
        Actions.Add(NewAction);
    }
}

bool UARPGActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
    for (UARPGActionBase* Action : Actions)
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
    for (UARPGActionBase* Action : Actions)
    {
        if (Action && Action->GetActionName() == ActionName)
        {
            Action->StopAction(Action, Instigator);
            return true;
        }
    }
    return false;
}