// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ARPGGameplayFunctionLibrary.generated.h"

struct FGameplayTag;
class UARPGAbilitySystemComponent;


// UENUM()
// enum class EARPGConfirmType : uint8
// {
// 	True,
// 	False
// };

UCLASS()
class ACTIONRPG_API UARPGGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION()
	static void ApplyDirectionalDamage(AActor* Instigator, AActor* Target, float Damage, float ImpulseMultiplier, const FHitResult& HitResult);

	static UARPGAbilitySystemComponent* NativeGetARPGAbilitySystemComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "ARPG|FunctionLibrary")
	static void AddGameplayTagToActor(AActor* Actor, FGameplayTag Tag); 

	UFUNCTION(BlueprintCallable, Category = "ARPG|FunctionLibrary")
	static void RemoveGameplayTagFromActor(AActor* Actor, FGameplayTag Tag);

	static bool NativeActorHasTag(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "ARPG|FunctionLibrary", meta = (DisplayName = "Actor Has Tag", ExpandBoolAsExecs = "ReturnValue"))
	static bool BP_DoesActorHaveTag(AActor* InActor,FGameplayTag TagToCheck);
	
};
