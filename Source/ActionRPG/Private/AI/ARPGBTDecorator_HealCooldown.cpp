// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARPGBTDecorator_HealCooldown.h"

#include "BehaviorTree/BlackboardComponent.h"

bool UARPGBTDecorator_HealCooldown::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return false;
	}
	
	const float LastHealTime = BlackboardComponent->GetValueAsFloat(LastHealTimeKey.SelectedKeyName);
	const float CurrentTime = GetWorld()->TimeSeconds;
	const bool bIsCanHeal = (LastHealTime == 0.0f) || (CurrentTime - LastHealTime >= CooldownTime);

	return bIsCanHeal;
}
