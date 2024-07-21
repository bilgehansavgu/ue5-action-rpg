#include "ActionRPG/Public/Core/Projectiles/ARPGProjectileBase.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/ARPGAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AARPGProjectileBase::AARPGProjectileBase()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName("Projectile");
	RootComponent = SphereComponent;

	EffectComponent = CreateDefaultSubobject<UNiagaraComponent>("EffectComponent");
	EffectComponent->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bInitialVelocityInLocalSpace = true;
	MovementComponent->ProjectileGravityScale = 0.f;
	MovementComponent->InitialSpeed = 4000;

	
}

void AARPGProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnActorOverlap);
	SphereComponent->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnActorHit);
}

UE_DISABLE_OPTIMIZATION
void AARPGProjectileBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		Explode();

		UARPGAttributeComponent* AttributeComponent = Cast<UARPGAttributeComponent>(OtherActor->GetComponentByClass(UARPGAttributeComponent::StaticClass()));

		if (AttributeComponent)
		{
			AttributeComponent->ApplyHealthChange(-Damage);
			
			if (GEngine)
			{
				FString DebugMessage = FString::Printf(TEXT("Health changed. New Health: %f"), AttributeComponent->GetHealth());
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Attribute Component found on %s"), *OtherActor->GetName());
		}
	}
}
UE_ENABLE_OPTIMIZATION

void AARPGProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AARPGProjectileBase::Explode_Implementation()
{
	if(ensure(IsValid(this)))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, GetActorLocation(), GetActorRotation());
		if(ExplodeSoundCue)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ExplodeSoundCue, GetActorLocation());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ExplosionSoundCue is not set on %s"), *GetName());
		}
		Destroy();
	}
}