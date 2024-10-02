// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARPGBTService_CheckHealth.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ARPGAttributeComponent.h"

class UARPGAttributeComponent;

void UARPGBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ensure(AIPawn))
	{
		return;
	}
	
	const UARPGAttributeComponent* AttributeComponent = UARPGAttributeComponent::GetAttributeComponent(AIPawn);
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!ensure(AttributeComponent) || !ensure(BlackboardComponent))
	{
		return;
	}

	BlackboardComponent->SetValueAsBool(ShouldHideAndHealKey.SelectedKeyName, AttributeComponent->GetHealthPercent() < LowHealthThreshold);
}
