// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ARPGAbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ARPGAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ACTIONRPG_API UARPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UARPGAttributeSet();
	
	UPROPERTY(BlueprintReadOnly, Category="ARPG|Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category="ARPG|Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category="ARPG|Rage")
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, CurrentRage)

	UPROPERTY(BlueprintReadOnly, Category="ARPG|Rage")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, MaxRage)

	UPROPERTY(BlueprintReadOnly, Category="ARPG|Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category="ARPG|Damage")
	FGameplayAttributeData DefencePower;
	ATTRIBUTE_ACCESSORS(UARPGAttributeSet, DefencePower)
};
