// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARPGBTTask_HealSelf.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ARPGAttributeComponent.h"

class UARPGAttributeComponent;

EBTNodeResult::Type UARPGBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	
	if (!AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	UARPGAttributeComponent* AttributeComponent = UARPGAttributeComponent::GetAttributeComponent(AIPawn);

	if (!ensure(AttributeComponent))
	{
		return EBTNodeResult::Failed;
	}
	
	AttributeComponent->ApplyHealthChange(AIPawn, AttributeComponent->GetMaxHealth());
	const float CurrentTime = GetWorld()->GetTimeSeconds();

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if(!ensure(BlackboardComponent))
	{
		return EBTNodeResult::Failed;
	}
	
	BlackboardComponent->SetValueAsFloat(LastHealTimeKey.SelectedKeyName, CurrentTime);

	return EBTNodeResult::Succeeded;
}
