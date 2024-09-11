// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARPG_BTServiceCheckAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UARPG_BTServiceCheckAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                         float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if(UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent(); ensure(BlackboardComponent))
	{
		if(AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor")))
		{
			if(AAIController* AIController = OwnerComp.GetAIOwner(); ensure(AIController))
			{
				if(APawn* AIPawn = AIController->GetPawn())
				{
					float Distance = FVector::Distance(AIPawn->GetActorLocation(), TargetActor->GetActorLocation());

					bool bIsInRange = Distance <= AttackRange;
					bool bHasLineOfSight = false;

					if (bIsInRange)
					{
						bHasLineOfSight = AIController->LineOfSightTo(TargetActor);
					}

					BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bIsInRange && bHasLineOfSight));
				}
			}
		}
	}
}
