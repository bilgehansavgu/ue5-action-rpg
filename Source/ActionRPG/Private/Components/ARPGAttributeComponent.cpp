// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGAttributeComponent.h"


UARPGAttributeComponent::UARPGAttributeComponent()
{
}

bool UARPGAttributeComponent::ApplyHealthChange(float DeltaHealth)
{
	float OldHealth = Health;
	Health = FMath::Clamp(Health + DeltaHealth, 0.f, MaxHealth);
	float AppliedDeltaHealth = Health - OldHealth;

	OnHealthChanged.Broadcast(nullptr, this, Health, AppliedDeltaHealth);
	
	return AppliedDeltaHealth != 0.f;
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
