// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/ARPGGameplayFunctionLibrary.h"

#include "Characters/ARPGCharacterBeard.h"
#include "Components/ARPGAbilitySystemComponent.h"
#include "Components/ARPGAttributeComponent.h"
#include "Types/ARPGEnumTypes.h"

void UARPGGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* Instigator, AActor* Target, float Damage, float ImpulseMultiplier, const FHitResult& HitResult)
{
	if (UARPGAttributeComponent* AttributeComponent = UARPGAttributeComponent::GetAttributeComponent(Target))
	{
		AttributeComponent->ApplyHealthChange(Instigator, -Damage);
		if(UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(HitResult.GetComponent()))
		{
			if (PrimitiveComponent->IsSimulatingPhysics(HitResult.BoneName))
			{
				PrimitiveComponent->AddImpulseAtLocation(-HitResult.ImpactNormal * ImpulseMultiplier, HitResult.ImpactPoint, HitResult.BoneName);
			}
		}
	}
}

UARPGAbilitySystemComponent* UARPGGameplayFunctionLibrary::NativeGetARPGAbilitySystemComponentFromActor(AActor* Actor)
{
	check(Actor);

	AARPGCharacterBeard* Character = Cast<AARPGCharacterBeard>(Actor);
	if (!Character)
	{
		UE_LOG(LogTemp, Error, TEXT("NativeGetARPGAbilitySystemComponentFromActor: Failed to cast Actor to AARPGCharacterBeard"));
		return nullptr;
	}

	UARPGAbilitySystemComponent* AbilitySystemComponent = Cast<UARPGAbilitySystemComponent>(Character->GetARPGAbilitySystemComponent());
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("NativeGetARPGAbilitySystemComponentFromActor: Failed to cast AbilitySystemComponent"));
		return nullptr;
	}

	return AbilitySystemComponent;
}

void UARPGGameplayFunctionLibrary::AddGameplayTagToActor(AActor* Actor, FGameplayTag Tag)
{
	UARPGAbilitySystemComponent* AbilitySystemComponent = NativeGetARPGAbilitySystemComponentFromActor(Actor);

	if (!AbilitySystemComponent->HasMatchingGameplayTag(Tag))
	{
		AbilitySystemComponent->AddLooseGameplayTag(Tag);
	}
}

void UARPGGameplayFunctionLibrary::RemoveGameplayTagFromActor(AActor* Actor, FGameplayTag Tag)
{
	UARPGAbilitySystemComponent* AbilitySystemComponent = NativeGetARPGAbilitySystemComponentFromActor(Actor);
	
	if (AbilitySystemComponent->HasMatchingGameplayTag(Tag))
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(Tag);
	}
}

bool UARPGGameplayFunctionLibrary::NativeActorHasTag(AActor* Actor, FGameplayTag Tag)
{
	UARPGAbilitySystemComponent* AbilitySystemComponent = NativeGetARPGAbilitySystemComponentFromActor(Actor);
	
	return AbilitySystemComponent->HasMatchingGameplayTag(Tag);
}

bool UARPGGameplayFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	return NativeActorHasTag(InActor,TagToCheck);
}

UARPGCombatComponent* UARPGGameplayFunctionLibrary::NativeGetARPGCombatComponentFromActor(AActor* Actor)
{
	check(Actor);

	if (IARPGCombatComponentInterface* CombatInterface = Cast<IARPGCombatComponentInterface>(Actor))
	{
		return CombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UARPGCombatComponent* UARPGGameplayFunctionLibrary::BP_GetARPGCombatComponentFromActor(AActor* Actor, EARPGValidType& OutValidType)
{
	UARPGCombatComponent* CombatComponent = NativeGetARPGCombatComponentFromActor(Actor);

	OutValidType = CombatComponent ? EARPGValidType::Valid : EARPGValidType::Invalid;

	return CombatComponent;
}
