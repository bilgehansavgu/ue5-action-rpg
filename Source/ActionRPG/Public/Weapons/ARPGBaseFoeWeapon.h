// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/ARPGStructTypes.h"
#include "ARPGBaseFoeWeapon.generated.h"

class UBoxComponent;
struct FGameplayAbilitySpecHandle;

UCLASS()
class ACTIONRPG_API AARPGBaseFoeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AARPGBaseFoeWeapon();
	
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
