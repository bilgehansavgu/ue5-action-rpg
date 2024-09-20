// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ARPGWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/ARPGAttributeComponent.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"


void UARPGWorldUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (UARPGAttributeComponent* AttributeComponent = UARPGAttributeComponent::GetAttributeComponent(AttachedActor))
    {
        AttributeComponent->OnHealthChanged.AddDynamic(this, &UARPGWorldUserWidget::OnHealthChangedCallback);
    }
}

void UARPGWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!AttachedActor)
	{
		return;
	}
	
	FVector2D ScreenPosition;
	if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation() + HealthBarOffset, ScreenPosition))
	{
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

		ScreenPosition /= Scale;

		if (SizeBox)
		{
			SizeBox->SetRenderTranslation(ScreenPosition);
		}
	}
}

void UARPGWorldUserWidget::OnHealthChangedCallback(AActor* InstigatorActor,
	UARPGAttributeComponent* AttributeComponent, float NewHealth, float DeltaHealth)
{
	if (!AttributeComponent->IsAlive())
	{
		HealthBar->RemoveFromParent();
	}
	
	if (HealthBar)
	{
		HealthBar->SetPercent(AttributeComponent->GetHealthPercent());
	}
}
