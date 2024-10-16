// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARPGProjectileBase.generated.h"

class USoundCue;
class UNiagaraSystem;
class UNiagaraComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class ACTIONRPG_API AARPGProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	

	AARPGProjectileBase();

protected:

	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent,
						AActor* OtherActor,
						UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex,
						bool bFromSweep,
						const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	UPROPERTY(EditDefaultsOnly, Category = "ARPG|Effects")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components")
	TObjectPtr<UProjectileMovementComponent> MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ARPG|Components")
	TObjectPtr<UNiagaraComponent> EffectComponent;

	UPROPERTY(EditDefaultsOnly, Category = "ARPG|Audio")
	TObjectPtr<USoundBase> ExplodeSoundCue;

	UPROPERTY(EditDefaultsOnly, Category = "ARPG|Stats")
	float Damage{20.f};

	UPROPERTY(EditDefaultsOnly, Category = "ARPG|Stats")
	float ImpulseMultiplier{0.f};
};