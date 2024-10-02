// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGAttributeComponent.h"

#include "GameModes/ARPGBaseGameMode.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("arpg.DamageMultiplier"), 1.f, TEXT("Global Damage Multiplier"), ECVF_Cheat);

void UARPGAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float DeltaHealth)
{
	if(Health <= 0.f)
	{
		return;
	}

	DeltaHealth *= CVarDamageMultiplier.GetValueOnGameThread();
	
	float OldHealth = Health;
	Health = FMath::Clamp(Health + DeltaHealth, 0.f, MaxHealth);
	float AppliedDeltaHealth = Health - OldHealth;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Health: %f"), Health));
	
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, AppliedDeltaHealth);

	if (Health == 0.f)
	{
		if(AARPGBaseGameMode* GameMode = GetWorld()->GetAuthGameMode<AARPGBaseGameMode>())
		{
			GameMode->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}
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