// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ARPGAction.h"

void UARPGAction::StartAction_Implementation(UARPGAction* Action, AActor* Instigator)
{
    UE_LOG(LogTemp, Log, TEXT("Action %s started by %s"), *GetNameSafe(Action), *GetNameSafe(Instigator));
}

void UARPGAction::StopAction_Implementation(UARPGAction* Action, AActor* Instigator)
{
    UE_LOG(LogTemp, Log, TEXT("Action %s stopped by %s"), *GetNameSafe(Action), *GetNameSafe(Instigator));
}