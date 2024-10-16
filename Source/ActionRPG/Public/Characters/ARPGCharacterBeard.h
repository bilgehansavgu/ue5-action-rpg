// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Components/ARPGAbilitySystemComponent.h"
#include "Interfaces/ARPGCombatComponentInterface.h"
#include "ARPGCharacterBeard.generated.h"


class UARPGPlayerCombatComponent;
class UARPGDataAsset_PlayerInit;
class UARPGAttributeSet;
class UARPGAbilitySystemComponent;
class UCameraComponent;
class USpringArmComponent;
class UARPGDataAsset_InputConfig;
struct FInputActionValue;

UCLASS()
class ACTIONRPG_API AARPGCharacterBeard : public ACharacter, public IAbilitySystemInterface, public IARPGCombatComponentInterface
{
	GENERATED_BODY()

public:
	AARPGCharacterBeard();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return GetARPGAbilitySystemComponent(); }
	//~ End IAbilitySystemInterface Interface
	
	FORCEINLINE UARPGAbilitySystemComponent* GetARPGAbilitySystemComponent() const { return AbilitySystemComponent; }

	FORCEINLINE UARPGAttributeSet* GetAttributeSet() const { return AttributeSet; }

	FORCEINLINE UARPGPlayerCombatComponent* GetCombatComponent() const { return CombatComponent; }

	//~ Begin IARPGCombatComponentInterface Interface.
	virtual UARPGCombatComponent* GetPawnCombatComponent() const override;
	//~ End IARPGCombatComponentInterface Interface
	
protected:
	virtual void BeginPlay() override;

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	UFUNCTION()
	void Input_Move(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void Input_Look(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void Input_AbilityInputPressed(FGameplayTag InputTag);

	UFUNCTION()
	void Input_AbilityInputReleased(FGameplayTag InputTag);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components")
	TObjectPtr<UARPGAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|AbilitySystem")
	TObjectPtr<UARPGAttributeSet> AttributeSet;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components")
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ARPG|CharacterData")
	TObjectPtr<UARPGDataAsset_InputConfig> InputConfigDataAsset;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ARPG|CharacterData")
	TSoftObjectPtr<UARPGDataAsset_PlayerInit> CharacterInitDataAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UARPGPlayerCombatComponent> CombatComponent;
};
