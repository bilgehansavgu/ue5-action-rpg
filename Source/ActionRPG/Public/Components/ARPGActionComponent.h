// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARPGActionComponent.generated.h"

class UARPGAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API UARPGActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category= "Actions")
	void AddAction(TSubclassOf<UARPGAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category= "Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);
	
	UFUNCTION(BlueprintCallable, Category= "Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Actions")
	TArray<TSubclassOf<UARPGAction>> DefaultActions;

	UPROPERTY()
	TArray<TObjectPtr<UARPGAction>> Actions;
};
