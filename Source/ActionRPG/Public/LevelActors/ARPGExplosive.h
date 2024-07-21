#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARPGExplosive.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONRPG_API AARPGExplosive : public AActor
{
	GENERATED_BODY()
	
public:	
	AARPGExplosive();

protected:
	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URadialForceComponent> RadialForceComponent;
};