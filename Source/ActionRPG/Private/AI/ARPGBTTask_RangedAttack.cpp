// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARPGBTTask_RangedAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Projectiles/ARPGProjectileBase.h"

EBTNodeResult::Type UARPGBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
                                                          uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if(ensure(AIController))
	{
		if(ACharacter* AICharacter = Cast<ACharacter>(AIController->GetPawn()))
		{
			FVector SpawnLocation  = AICharacter->GetMesh()->GetSocketLocation(ProjectileSpawnSocketName);

			if(AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor")))
			{
				FVector Direction = TargetActor->GetActorLocation() - SpawnLocation ;
				
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				SpawnParameters.Instigator = AICharacter;

				if(ensure(ProjectileClass); AARPGProjectileBase* Projectile = GetWorld()->SpawnActor<AARPGProjectileBase>(ProjectileClass, SpawnLocation , Direction.Rotation(), SpawnParameters))
				{
					Projectile->SetOwner(AICharacter);
					return EBTNodeResult::Succeeded;
				}
				
				return EBTNodeResult::Failed;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}
