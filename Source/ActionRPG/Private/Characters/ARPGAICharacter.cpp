// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGAICharacter.h"

#include "BrainComponent.h"
#include "AI/ARPGAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/ARPGAttributeComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Widgets/ARPGWorldUserWidget.h"

class AARPGAIController;

AARPGAICharacter::AARPGAICharacter()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	AttributeComponent = CreateDefaultSubobject<UARPGAttributeComponent>(TEXT("AttributeComponent"));
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// To make AI Character's capsule component not collide with projectiles so that projectile can apply impulsive damage to hit result bones
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

void AARPGAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AARPGAICharacter::OnSeePawnCallback);
	AttributeComponent->OnHealthChanged.AddUniqueDynamic(this, &AARPGAICharacter::OnHealthChangedCallback);
}

bool AARPGAICharacter::SetTargetActor(AActor* NewTarget)
{
	if (AARPGAIController* AIController = Cast<AARPGAIController>(GetController()); NewTarget)
	{
		if (UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsObject("TargetActor", NewTarget);
#if WITH_EDITOR
			DrawDebugString(GetWorld(), GetActorLocation(), "I see you!", nullptr, FColor::Red, 0.5f);
#endif
			
			return true;
		}
	}
	return false;
}

void AARPGAICharacter::OnSeePawnCallback(APawn* Pawn)
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

void AARPGAICharacter::OnHealthChangedCallback(AActor* InstigatorActor,
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

	if (HealthBarWidget == nullptr)
	{
		HealthBarWidget = CreateWidget<UARPGWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
		if (HealthBarWidget)
		{
			HealthBarWidget->OnHealthChangedCallback(InstigatorActor, OwningComponent, NewHealth, DeltaHealth);
			HealthBarWidget->AttachedActor = this;
			HealthBarWidget->AddToViewport();
		}
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

