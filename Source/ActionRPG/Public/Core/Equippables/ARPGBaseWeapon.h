// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Equippables/ARPGBaseEquippable.h"
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
	void SetEquippedSocketName(FName SocketName);

	UFUNCTION()
	void SetUnequippedSocketName(FName SocketName);
		
	UFUNCTION()
	void OnEquipped(AActor* Actor);

	UFUNCTION()
	void OnUnequipped(AActor* Actor);

	UPROPERTY(EditAnywhere)
	FName EquippedSocketName;

	UPROPERTY(EditAnywhere)
	FName UnequippedSocketName;
};
