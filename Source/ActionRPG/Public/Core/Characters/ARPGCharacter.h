// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGCharacter.generated.h"

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
	void PutBackWeapon();

	UFUNCTION()
	void DrawWeapon();
	
	UFUNCTION()
	AARPGBaseEquippable* GetMainWeapon();

	UFUNCTION()
	void SetMainWeapon(AARPGBaseEquippable* WeaponClass);

	UFUNCTION()
	void PickUpWeapon(TSubclassOf<AARPGBaseEquippable> WeaponClass);

	// UFUNCTION()
	// void DropWeapon();

protected:

	//	DELEGATES


	//	FUNCTIONS

	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void Move(const FInputActionInstance& Instance);

	UFUNCTION()
	void LookMouse(const FInputActionValue& Value);

	UFUNCTION()
	void SpawnProjectile(TSubclassOf<AARPGProjectileBase> ClassToSpawn);

	UFUNCTION()
	void BasicAttack();

	UFUNCTION()
	void AreaOfEffectAttack();

	UFUNCTION()
	void Teleport();

	UFUNCTION()
	void ToggleMainWeaponMontage();

	UFUNCTION()
	void OnHealthChangedEvent(AActor* InstigatorActor, UARPGAttributeComponent* OwningComponent, float NewHealth, float DeltaHealth);

	UFUNCTION()
	void TookDamageMaterialEffect();

	UFUNCTION()
	void HPBuffMaterialEffect();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void ToggleInventory();

	// PROPERTIES
	
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName RightHandSocketName{"ik_hand_rSocket"};

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UARPGInteractionComponent> InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UARPGAttributeComponent> AttributeComponent;

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

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimMontage> DisarmGreatSwordAnimation;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AARPGProjectileBase> BasicAttackProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AARPGProjectileBase> AreaOfEffectClass;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AARPGProjectileBase> TeleportSpellClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float ProjectileTraceEndDistance{5000.f};
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float ProjectileTraceRadius{20.f};

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<AARPGBaseEquippable> MainWeapon;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool bIsWeaponEquipped = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY()
	UUserWidget* InventoryWidget;
	
	bool bIsInventoryOpen = false;
};
