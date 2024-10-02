// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARPGActionComponent.generated.h"

class UARPGActionBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONRPG_API UARPGActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category= "ARPG|Actions")
	void AddAction(TSubclassOf<UARPGActionBase> ActionClass);

	UFUNCTION(BlueprintCallable, Category= "ARPG|Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category= "ARPG|Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "ARPG|Actions")
	TArray<TSubclassOf<UARPGActionBase>> DefaultActions;

	UPROPERTY()
	TArray<TObjectPtr<UARPGActionBase>> Actions;
};
