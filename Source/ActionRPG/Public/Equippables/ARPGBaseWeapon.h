// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equippables/ARPGBaseEquippable.h"
#include "ARPGBaseWeapon.generated.h"

UCLASS()
class ACTIONRPG_API AARPGBaseWeapon : public AARPGBaseEquippable
{
	GENERATED_BODY()

public:

	AARPGBaseWeapon() = default;

	UFUNCTION()
	FName GetEquippedSocketName() const;

	UFUNCTION()
	FName GetUnequippedSocketName() const;

	UFUNCTION()
	void OnEquipped(AActor* Actor);

	UFUNCTION()
	void OnUnequipped(AActor* Actor);

	UFUNCTION()
	UAnimMontage* GetDrawAnimationMontage() const;

	UFUNCTION()
	UAnimMontage* GetDisarmAnimationMontage() const;

protected:

	UFUNCTION()
	void SetEquippedSocketName(FName SocketName);

	UFUNCTION()
	void SetUnequippedSocketName(FName SocketName);
	
	UPROPERTY(EditAnywhere, Category = "ARPG|Socket")
	FName EquippedSocketName;

	UPROPERTY(EditAnywhere, Category = "ARPG|Socket")
	FName UnequippedSocketName;
	
	UPROPERTY(EditAnywhere, Category = "ARPG|Animation")
	TObjectPtr<UAnimMontage> DrawAnimation;

	UPROPERTY(EditAnywhere, Category = "ARPG|Animation")
	TObjectPtr<UAnimMontage> DisarmAnimation;
};
