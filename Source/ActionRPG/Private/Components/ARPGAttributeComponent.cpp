// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGAttributeComponent.h"


UARPGAttributeComponent::UARPGAttributeComponent()
{
}

bool UARPGAttributeComponent::ApplyHealthChange(float DeltaHealth)
{
	Health += DeltaHealth;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(nullptr, this, Health, DeltaHealth);
	
	return true;
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
