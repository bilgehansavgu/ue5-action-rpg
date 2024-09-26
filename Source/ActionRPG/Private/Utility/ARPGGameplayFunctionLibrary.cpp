// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/ARPGGameplayFunctionLibrary.h"

#include "Components/ARPGAttributeComponent.h"

void UARPGGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* Instigator, AActor* Target, float Damage, float ImpulseMultiplier, const FHitResult& HitResult)
{
	if (UARPGAttributeComponent* AttributeComponent = UARPGAttributeComponent::GetAttributeComponent(Target))
	{
		AttributeComponent->ApplyHealthChange(Instigator, -Damage);
		if(UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(HitResult.GetComponent()))
		{
			if (PrimitiveComponent->IsSimulatingPhysics(HitResult.BoneName))
			{
				PrimitiveComponent->AddImpulseAtLocation(-HitResult.ImpactNormal * ImpulseMultiplier, HitResult.ImpactPoint, HitResult.BoneName);
			}
		}
	}
}
