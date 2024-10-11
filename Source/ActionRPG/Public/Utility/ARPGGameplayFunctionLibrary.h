// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ARPGGameplayFunctionLibrary.generated.h"

enum class EARPGValidType : uint8;
class UARPGCombatComponent;
struct FGameplayTag;
class UARPGAbilitySystemComponent;


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

	static UARPGCombatComponent* NativeGetARPGCombatComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "ARPG|FunctionLibrary", meta = (DisplayName = "Get ARPG Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UARPGCombatComponent* BP_GetARPGCombatComponentFromActor(AActor* Actor, EARPGValidType& OutValidType);
	
};
