// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARPGAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API UARPGAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UARPGAttributeComponent*, AttributeComponent, float, NewHealth, float, DeltaHealth);

public:	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	UFUNCTION(BlueprintCallable)
	void ApplyHealthChange(AActor* InstigatorActor, float DeltaHealth);

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsAlive() const {return Health > 0.f;}

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetHealth() const {return Health;}

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetHealthPercent() const {return Health / MaxHealth;}

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetMaxHealth() const {return MaxHealth;}

	UFUNCTION(BlueprintCallable, Category="ARPG|Attributes", meta=( DisplayName="Is Alive"))
	static bool IsActorAlive(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="ARPG|Attributes")
	static UARPGAttributeComponent* GetAttributeComponent(AActor* Actor);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ARPG|Attributes")
	float Health{100.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ARPG|Attributes")
	float MaxHealth{100.f};
};
