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
	void PutBackWeapon() const;

	UFUNCTION()
	void DrawWeapon() const;

protected:

	//	DELEGATES


	//	FUNCTIONS
	
	virtual void BeginPlay() override;
	
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
	void SpawnWeapon();

	UFUNCTION()
	void ToggleMainWeaponMontage();

	UFUNCTION()
	void OnHealthChangedEvent(AActor* InstigatorActor, UARPGAttributeComponent* OwningComponent, float NewHealth, float DeltaHealth);

	UFUNCTION()
	void TookDamageMaterialEffect() const;

	UFUNCTION()
	void HPBuffMaterialEffect() const;

	UFUNCTION()
	void Interact();

	// PROPERTIES
	
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName RightHandSocketName{"ik_hand_rSocket"};
	
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName BigSwordHipLSocketName{"sword_hip_attach_socket"};

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName BigSwordHandRSocketName{"hand_r_weapon_socket"};

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

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimMontage> DrawWeaponAnimation;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimMontage> PutBackWeaponAnimation;

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
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AARPGBaseEquippable> WeaponClass;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<AARPGBaseEquippable> MainWeapon;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool bIsWeaponEquipped = false;
};
