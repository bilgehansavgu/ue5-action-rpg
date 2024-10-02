// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGAICharacter.generated.h"

class UARPGWorldUserWidget;
class UARPGAttributeComponent;
class UPawnSensingComponent;

UCLASS()
class ACTIONRPG_API AARPGAICharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AARPGAICharacter();

protected:

	UFUNCTION()
	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	bool SetTargetActor(AActor* NewTarget);
	
	UFUNCTION()
	void OnSeePawnCallback(APawn* Pawn);

	UFUNCTION()
	void OnHealthChangedCallback(AActor* InstigatorActor,UARPGAttributeComponent* OwningComponent, float NewHealth, float DeltaHealth);
	
	UPROPERTY(VisibleAnywhere, Category="ARPG|Components")
	TObjectPtr<UPawnSensingComponent> PawnSensingComponent;
	
	UPROPERTY(VisibleAnywhere, Category="ARPG|Components")
	TObjectPtr<UARPGAttributeComponent> AttributeComponent;

	UPROPERTY(EditDefaultsOnly, Category="ARPG|UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY()
	TObjectPtr<UARPGWorldUserWidget> HealthBarWidget;
};
