// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Components/ARPGAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/ARPGCombatComponentInterface.h"
#include "ARPGCharacterFoe.generated.h"

class UARPGAttributeSet;
class UARPGAbilitySystemComponent;
class UARPGDataAsset_FoeInit;
class UARPGFoeCombatComponent;

UCLASS()
class ACTIONRPG_API AARPGCharacterFoe : public ACharacter, public IAbilitySystemInterface, public IARPGCombatComponentInterface
{
	GENERATED_BODY()

public:
	AARPGCharacterFoe();

	FORCEINLINE UARPGFoeCombatComponent* GetFoeCombatComponent() const { return FoeCombatComponent;}
	
	//~ Begin IARPGCombatComponentInterface Interface.
	virtual UARPGCombatComponent* GetPawnCombatComponent() const override;
	//~ End IARPGCombatComponentInterface Interface
	
protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	//~ End IAbilitySystemInterface Interface

	UFUNCTION()
	void InitData();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components")
	TObjectPtr<UARPGAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components")
	TObjectPtr<UARPGFoeCombatComponent> FoeCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|AbilitySystem")
	TObjectPtr<UARPGAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ARPG|CharacterData")
	TSoftObjectPtr<UARPGDataAsset_FoeInit> FoeInitDataAsset;

};
