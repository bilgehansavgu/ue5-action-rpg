// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGAttributeComponent.h"


UARPGAttributeComponent::UARPGAttributeComponent()
{
}

bool UARPGAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float DeltaHealth)
{
	float OldHealth = Health;
	Health = FMath::Clamp(Health + DeltaHealth, 0.f, MaxHealth);
	float AppliedDeltaHealth = Health - OldHealth;

	if (AppliedDeltaHealth != 0.f)
	{
		OnHealthChanged.Broadcast(InstigatorActor, this, Health, AppliedDeltaHealth);
		return true;
	}
	
	return false;
}

bool UARPGAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}

float UARPGAttributeComponent::GetHealth() const
{
	return Health;
}

float UARPGAttributeComponent::GetHealthPercent() const
{
	return Health / MaxHealth;
}

bool UARPGAttributeComponent::IsActorAlive(AActor* Actor)
{
	if (Actor)
	{
		if (UARPGAttributeComponent* AttributeComponent = Actor->FindComponentByClass<UARPGAttributeComponent>())
		{
			return AttributeComponent->IsAlive();
		}
	}
	return false;
}

UARPGAttributeComponent* UARPGAttributeComponent::GetAttributeComponent(AActor* Actor)
{
	if (Actor)
	{
		return Actor->FindComponentByClass<UARPGAttributeComponent>();
	}
	return nullptr;
}