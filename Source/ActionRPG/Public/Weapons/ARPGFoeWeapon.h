// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGWeapon.h"
#include "GameFramework/Actor.h"
#include "Types/ARPGStructTypes.h"
#include "ARPGFoeWeapon.generated.h"

class UBoxComponent;
struct FGameplayAbilitySpecHandle;

UCLASS()
class ACTIONRPG_API AARPGFoeWeapon : public AARPGWeapon
{
	GENERATED_BODY()
	
public:	
	AARPGFoeWeapon();
	
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
	FARPGFoeWeaponData FoeWeaponData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ARPG|WeaponData")
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;

};
