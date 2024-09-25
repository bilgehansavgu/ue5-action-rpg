// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ARPGActionBase.h"

void UARPGActionBase::StartAction_Implementation(UARPGActionBase* Action, AActor* Instigator)
{
    UE_LOG(LogTemp, Log, TEXT("Action %s started by %s"), *GetNameSafe(Action), *GetNameSafe(Instigator));
}

void UARPGActionBase::StopAction_Implementation(UARPGActionBase* Action, AActor* Instigator)
{
    UE_LOG(LogTemp, Log, TEXT("Action %s stopped by %s"), *GetNameSafe(Action), *GetNameSafe(Instigator));
}

UWorld* UARPGActionBase::GetWorld() const
{
    UActorComponent* OwnerComponent = Cast<UActorComponent>(GetOuter());
    
    return OwnerComponent ? OwnerComponent->GetWorld() : nullptr;
}
