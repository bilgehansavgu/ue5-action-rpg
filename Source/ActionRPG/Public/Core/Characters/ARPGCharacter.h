// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGCharacter.generated.h"

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

protected:

	//	DELEGATES


	//	FUNCTIONS
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void Move(const FInputActionInstance& Instance);

	UFUNCTION()
	void LookMouse(const FInputActionValue& Value);

	UFUNCTION()
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	UFUNCTION()
	void BasicAttack();

	UFUNCTION()
	void AreaOfEffectAttack();

	UFUNCTION()
	void Teleport();

	UFUNCTION()
	void SpawnWeapon();

	UFUNCTION()
	void ToggleMainWeapon();

	// PROPERTIES
	
	UPROPERTY(EditDefaultsOnly)
	float ProjectileTraceEndDistance{5000.f};

	UPROPERTY(EditDefaultsOnly)
	float ProjectileTraceRadius{20.f};
	
	UPROPERTY(EditDefaultsOnly)
	FName RightHandSocketName{"ik_hand_rSocket"};
	
	UPROPERTY(EditDefaultsOnly)
	FName BigSwordHipLSocketName{"sword_hip_attach_socket"};

	UPROPERTY(EditDefaultsOnly)
	FName BigSwordHandRSocketName{"hand_r_weapon_socket"};

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

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
	TObjectPtr<UInputAction> Input_EquipWeapon;

	UPROPERTY(EditAnywhere, Category = "Animations")
	TObjectPtr<UAnimMontage> AttackAnimation;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BasicAttackProjectileClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> AreaOfEffectClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> TeleportSpellClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> WeaponClass;
	
	AActor* MainWeapon;
};
