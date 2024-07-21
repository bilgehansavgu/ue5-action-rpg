// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGInteractionComponent.h"

#include "Core/Interfaces/ARPGInteractableInterface.h"


UARPGInteractionComponent::UARPGInteractionComponent()
{

}

void UARPGInteractionComponent::Interact()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	AActor* Owner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector EndLocation = EyeLocation + (EyeRotation.Vector() * EndDistance);
	
	/*FHitResult HitResult;
	bool bIsHit = GetWorld()->LineTraceSingleByObjectType(HitResult, EyeLocation, EndLocation, ObjectQueryParams);*/

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(ShapeRadius);

	TArray<FHitResult> HitResults;
	bool bIsHit = GetWorld()->SweepMultiByObjectType(HitResults, EyeLocation, EndLocation, FQuat::Identity, ObjectQueryParams, CollisionShape);

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
				
				break;
			}
		}

		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, ShapeRadius, 32, DebugColor, false, 2.f);
	}
	
	DrawDebugLine(GetWorld(), EyeLocation, EndLocation, DebugColor, false, 2.f, 0.f, 2.f);
}

