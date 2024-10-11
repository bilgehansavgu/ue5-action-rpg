// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGCharacterFoe.generated.h"

class UARPGAbilitySystemComponent;
class UARPGDataAsset_FoeInit;
class UARPGFoeCombatComponent;

UCLASS()
class ACTIONRPG_API AARPGCharacterFoe : public ACharacter
{
	GENERATED_BODY()

public:
	AARPGCharacterFoe();

	FORCEINLINE UARPGFoeCombatComponent* GetFoeCombatComponent() const { return FoeCombatComponent;}
	
protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UFUNCTION()
	void InitData();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components")
	TObjectPtr<UARPGAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components")
	TObjectPtr<UARPGFoeCombatComponent> FoeCombatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ARPG|CharacterData")
	TSoftObjectPtr<UARPGDataAsset_FoeInit> FoeInitDataAsset;

};
