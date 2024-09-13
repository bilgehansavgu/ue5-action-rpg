// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelActors/ARPGHealthPotion.h"

#include "Components/ARPGAttributeComponent.h"


AARPGHealthPotion::AARPGHealthPotion()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionProfileName("Powerup");
	RootComponent = StaticMesh;
}

void AARPGHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	UARPGAttributeComponent* AttributeComponent = InstigatorPawn->FindComponentByClass<UARPGAttributeComponent>();

	if(AttributeComponent)
	{
		if (AttributeComponent->GetHealthPercent() == 1.f)
		{
			return;
		}

		AttributeComponent->ApplyHealthChange(BuffAmount);
		
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		// RootComponent->SetVisibility(true, true);
		// SetActorEnableCollision(false);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AARPGHealthPotion::EnablePotion, 10.0f, false);
	}
}

void AARPGHealthPotion::EnablePotion()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}


