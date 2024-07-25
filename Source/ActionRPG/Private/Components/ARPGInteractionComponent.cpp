// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGInteractionComponent.h"

#include "Core/Interfaces/ARPGInteractableInterface.h"
#include "Kismet/GameplayStatics.h"


UARPGInteractionComponent::UARPGInteractionComponent()
{

}

void UARPGInteractionComponent::Interact()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	AActor* Owner = GetOwner();
	
	APlayerController* PlayerController = Cast<APlayerController>(Owner->GetInstigatorController());
	if(PlayerController == nullptr)
	{
		return;
	}

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	FVector2D ScreenCenter = ViewportSize / 2.f;
	
	FVector WorldLocation, WorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(PlayerController, ScreenCenter, WorldLocation, WorldDirection);
	
	FVector TraceStart = WorldLocation;
	FVector TraceEnd = WorldLocation + (WorldDirection * EndDistance);

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(ShapeRadius);

	TArray<FHitResult> HitResults;
	bool bIsHit = GetWorld()->SweepMultiByObjectType(HitResults, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, CollisionShape);
	FColor DebugColor = bIsHit ? FColor::Green : FColor::Red;

	for(const FHitResult& HitResult : HitResults)
	{
		AActor* HitActor = HitResult.GetActor();
		if(HitActor)
		{
			if(HitActor->Implements<UARPGInteractableInterface>())
			{
				APawn* Pawn = Cast<APawn>(Owner);
			
				IARPGInteractableInterface::Execute_Interact(HitActor, Pawn);
				DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, ShapeRadius, 32, DebugColor, false, 2.f);
				break;
			}
		}
	}
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, DebugColor, false, 2.f, 0.f, 2.f);
}

