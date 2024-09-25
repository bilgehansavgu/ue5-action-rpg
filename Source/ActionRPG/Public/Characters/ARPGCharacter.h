// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGCharacter.generated.h"

class UARPGInventoryComponent;
class UARPGActionBase;
class UARPGActionComponent;
class UARPGAttributeComponent;
class UARPGInteractionComponent;
class AARPGBaseEquippable;
class AARPGProjectileBase;
class USpringArmComponent;
class UCameraComponent;

class UInputAction;
class UInputMappingContext;

struct FInputActionValue;
struct FInputActionInstance;

UCLASS()
class ACTIONRPG_API AARPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AARPGCharacter();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	UARPGInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

protected:

	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void Move(const FInputActionInstance& Instance);

	UFUNCTION()
	void LookMouse(const FInputActionValue& Value);

	UFUNCTION()
	void BasicRangedAttack();

	UFUNCTION()
	void AreaOfEffectAttack();
	
	UFUNCTION()
	void Teleport();

	UFUNCTION()
	void EquipMainWeapon();
	
	UFUNCTION()
	void OnHealthChangedEvent(AActor* InstigatorActor, UARPGAttributeComponent* OwningComponent, float NewHealth, float DeltaHealth);

	UFUNCTION()
	void TookDamageMaterialEffect() const;

	UFUNCTION()
	void HPBuffMaterialEffect() const;

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void ToggleInventory();

	UFUNCTION()
	void Sprint();

	UFUNCTION()
	void StopSprint();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UARPGInteractionComponent> InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UARPGAttributeComponent> AttributeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UARPGActionComponent> ActionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UARPGInventoryComponent> InventoryComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_LookMouse;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_BasicAttack;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_AreaOfEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Teleport;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Interact;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_EquipWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_DropWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_ToggleInventory;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Sprint;
};
