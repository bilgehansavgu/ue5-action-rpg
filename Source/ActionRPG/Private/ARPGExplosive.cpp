// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGExplosive.h"

#include "PhysicsEngine/RadialForceComponent.h"

AARPGExplosive::AARPGExplosive()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetSimulatePhysics(true);
	RootComponent = MeshComponent;
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(MeshComponent);
	RadialForceComponent->SetAutoActivate(false);
	RadialForceComponent->Radius = 750.f;
	RadialForceComponent->ImpulseStrength = 2500.f;
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

void AARPGExplosive::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MeshComponent->OnComponentHit.AddUniqueDynamic(this, &ThisClass::AARPGExplosive::OnComponentHit);
}

void AARPGExplosive::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComponent->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnComponent Triggered"))

	UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s, at Game Second : %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds)

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("This message will appear on the screen!"));

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x = %f, y = %f"), 2.f, 6.f));

	FString DebugString = FString::Printf(TEXT("Hit at Location : %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, DebugString, nullptr, FColor::Green, 3.f, true);
}
