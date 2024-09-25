
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARPGInventoryComponent.generated.h"


class AARPGBaseEquippable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API UARPGInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void ToggleInventoryWidget(AActor* InstigatorActor);

	UFUNCTION()
	void ToggleMainWeaponMontage(AActor* InstigatorActor);

	UFUNCTION()
	void PickUpWeapon(AActor* InstigatorActor, TSubclassOf<AARPGBaseEquippable> WeaponClass);
	
	UFUNCTION()
	void PutBackWeapon();

	UFUNCTION()
	void DrawWeapon();
	
	UFUNCTION()
	AARPGBaseEquippable* GetMainWeapon() const { return MainWeapon; }

	UFUNCTION()
	void SetMainWeapon(AARPGBaseEquippable* WeaponClass);
	
	// void AddItem(AARPGInventoryItem* Item);
	// void RemoveItem(AARPGInventoryItem* Item);
	// AARPGInventoryItem* GetItem(int32 Index) const;
	// int32 GetInventorySize() const;

protected:
	UPROPERTY(EditAnywhere)
	uint16 CoinAmount{0};

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<AARPGBaseEquippable> MainWeapon;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool bIsWeaponEquipped = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY()
	UUserWidget* InventoryWidget;
	
	bool bIsInventoryWidgetOpen = false;
};
