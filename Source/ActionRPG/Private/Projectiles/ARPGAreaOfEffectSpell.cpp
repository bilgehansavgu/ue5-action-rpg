// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectiles/ARPGAreaOfEffectSpell.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AARPGAreaOfEffectSpell::AARPGAreaOfEffectSpell()
{
	MovementComponent->ProjectileGravityScale = 4.0f;

	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AARPGAreaOfEffectSpell::Explode_Implementation()
{
	Super::Explode_Implementation();

	const FVector ActorLocation = GetActorLocation();
	const FVector Forward = GetActorForwardVector();

	TArray<TObjectPtr<AActor>> ActorsToIgnore{GetInstigator()};
	TArray<FHitResult> OutHits;

	const FVector TraceStart = ActorLocation + Forward * Radius;
	const FVector TraceEnd = ActorLocation - Forward * Radius;
	
	UKismetSystemLibrary::SphereTraceMultiForObjects(this,
													TraceStart,
													TraceEnd,
													Radius,
													ObjectTypes,
													false,
													ActorsToIgnore,
													EDrawDebugTrace::None,
													OutHits,
													true);
	
	for(const FHitResult& HitResult : OutHits)
	{
		if (HitResult.GetActor())
		{
			Explode();
			break;
		}
	}
}