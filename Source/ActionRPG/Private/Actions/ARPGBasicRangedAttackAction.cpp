// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ARPGBasicRangedAttackAction.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Projectiles/ARPGProjectileBase.h"

UARPGBasicRangedAttackAction::UARPGBasicRangedAttackAction()
{
}

void UARPGBasicRangedAttackAction::StartAction_Implementation(UARPGActionBase* Action,
	AActor* Instigator)
{
	Super::StartAction_Implementation(Action, Instigator);

	if (ACharacter* InstigatorCharacter = Cast<ACharacter>(Instigator))
	{
		SpawnProjectile(InstigatorCharacter);
	}
}

void UARPGBasicRangedAttackAction::StopAction_Implementation(UARPGActionBase* Action,
	AActor* Instigator)
{
	Super::StopAction_Implementation(Action, Instigator);
}

void UARPGBasicRangedAttackAction::SpawnProjectile(ACharacter* InstigatorCharacter)
{
	if(ensureAlways(BasicRangedAttackClass))
	{
		FVector RightHandSpawnLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(RightHandSocketName);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = InstigatorCharacter;

		FCollisionShape Shape;
		Shape.SetSphere(ProjectileTraceRadius);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		APlayerController* PlayerController = Cast<APlayerController>(InstigatorCharacter->GetController());
		if(PlayerController == nullptr)
		{
			return;
		}

		FVector2D ViewportSize;

		if (!(GEngine && GEngine->GameViewport))
		{
			return;
		}
		
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		FVector2D ScreenCenter = ViewportSize / 2.f;
	
		FVector WorldLocation, WorldDirection;
		UGameplayStatics::DeprojectScreenToWorld(PlayerController, ScreenCenter, WorldLocation, WorldDirection);
	
		FVector TraceStart = WorldLocation;
		FVector TraceEnd = WorldLocation + (WorldDirection * ProjectileTraceEndDistance);

		FHitResult HitResult;

		if(GetWorld()->SweepSingleByObjectType(HitResult, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, Shape, Params))
		{
			TraceEnd = HitResult.ImpactPoint;
		}

		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - RightHandSpawnLocation).Rotator();

		FTransform SpawnTransform = FTransform(ProjRotation, RightHandSpawnLocation);

		if (UWorld*	World = GetWorld())
		{
			World->SpawnActor<AActor>(BasicRangedAttackClass, SpawnTransform, SpawnParameters);
		}
	}
}
