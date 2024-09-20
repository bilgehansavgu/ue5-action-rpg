// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ARPGAttributeComponent.h"
#include "ARPGWorldUserWidget.generated.h"

class UProgressBar;
class USizeBox;

UCLASS()
class ACTIONRPG_API UARPGWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta=(ExposeOnSpawn = true))
	TObjectPtr<AActor> AttachedActor;

	UFUNCTION()
	void OnHealthChangedCallback(AActor* InstigatorActor, UARPGAttributeComponent* AttributeComponent, float NewHealth, float DeltaHealth);
	
protected:
	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(EditAnywhere, Category = "UI")
	FVector HealthBarOffset{0,0,100};
};
