// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameFramework/Actor.h"
#include "ARPGWeapon.generated.h"

class UBoxComponent;
struct FGameplayAbilitySpecHandle;

UCLASS()
class ACTIONRPG_API AARPGWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AARPGWeapon();

	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return CollisionBox;}

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle>& GetGrantedAbilitySpecHandles() {return GrantedAbilitySpecHandles;}

	UFUNCTION(BlueprintCallable)
	void SetGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& SpecHandles);

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components")
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ARPG|WeaponData")
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
