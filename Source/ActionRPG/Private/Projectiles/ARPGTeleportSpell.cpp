// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/ARPGTeleportSpell.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Characters/ARPGCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AARPGTeleportSpell::AARPGTeleportSpell()
{
	MovementComponent->InitialSpeed = 6000.f;

	Damage = 0.f;
}

void AARPGTeleportSpell::BeginPlay()
{
	Super::BeginPlay();

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DashEffect, GetInstigator()->GetActorLocation(), GetActorRotation());
	
	if(AARPGCharacter* Character = Cast<AARPGCharacter>(GetInstigator()))
	{
		Character->GetMovementComponent()->SetActive(false);
	}

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ThisClass::Explode, DetonateDelay);
}

void AARPGTeleportSpell::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);
	
	EffectComponent->Deactivate();

	MovementComponent->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ThisClass::TeleportInstigator, TeleportDelay);
}

void AARPGTeleportSpell::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if(ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, ActorToTeleport->GetActorLocation(), ActorToTeleport->GetActorRotation());

		if(AARPGCharacter* Character = Cast<AARPGCharacter>(ActorToTeleport))
		{
			Character->GetMovementComponent()->SetActive(true);
		}
	}
	
	Destroy();
}