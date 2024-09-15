// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGAICharacter.h"

#include "BrainComponent.h"
#include "AI/ARPGAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ARPGAttributeComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"

class AARPGAIController;

AARPGAICharacter::AARPGAICharacter()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	AttributeComponent = CreateDefaultSubobject<UARPGAttributeComponent>(TEXT("AttributeComponent"));
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

void AARPGAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AARPGAICharacter::OnSeePawn);
	AttributeComponent->OnHealthChanged.AddUniqueDynamic(this, &AARPGAICharacter::OnHealthChangedEvent);
}

void AARPGAICharacter::OnSeePawn(APawn* Pawn)
{
	if (AARPGAIController* AIController = Cast<AARPGAIController>(GetController()))
	{
		if (UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsObject("TargetActor", Pawn);
			DrawDebugString(GetWorld(), GetActorLocation(), "I see you!", nullptr, FColor::Red, 2.0f);
		}
	}

}

bool AARPGAICharacter::SetTargetActor(AActor* NewTarget)
{
	if (AARPGAIController* AIController = Cast<AARPGAIController>(GetController()); NewTarget)
	{
		if (UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsObject("TargetActor", NewTarget);
			#if WITH_EDITOR
				DrawDebugString(GetWorld(), GetActorLocation(), "I see you!", nullptr, FColor::Red, 2.0f);
			#endif
			
			return true;
		}
	}
	return false;
}

void AARPGAICharacter::OnHealthChangedEvent(AActor* InstigatorActor,
                                            UARPGAttributeComponent* OwningComponent, float NewHealth, float DeltaHealth)
{
	if (InstigatorActor == this)
	{
		return;
	}
	
	if (!SetTargetActor(InstigatorActor))
	{
		return;
	}

	if (NewHealth <= 0.0f)
	{
		if(AARPGAIController* AIController = Cast<AARPGAIController>(GetController()))
		{
			AIController->GetBrainComponent()->StopLogic("Killed");
		}
		
		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName("Ragdoll");
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		SetLifeSpan(10.f);
	}
}

