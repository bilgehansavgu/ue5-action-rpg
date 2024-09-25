// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ARPGInventoryComponent.h"

#include "Blueprint/UserWidget.h"
#include "Equippables/ARPGBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

class UARPGWeaponUnequipAnimNotifyState;
class AARPGCharacter;
class AARPGBaseWeapon;


void UARPGInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InventoryWidget = CreateWidget<UUserWidget>(GetOwner()->GetWorld(), InventoryWidgetClass);
}

void UARPGInventoryComponent::ToggleInventoryWidget(AActor* InstigatorActor)
{
	if (bIsInventoryWidgetOpen)
	{
		if (InventoryWidget)
		{
			InventoryWidget->RemoveFromParent();
		}

		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->SetShowMouseCursor(false);
		}
	}
	else
	{
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
		}

		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
			PlayerController->SetInputMode(InputMode);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	bIsInventoryWidgetOpen = !bIsInventoryWidgetOpen;
}

void UARPGInventoryComponent::PickUpWeapon(AActor* InstigatorActor, TSubclassOf<AARPGBaseEquippable> WeaponClass)
{
	if (!(WeaponClass && InstigatorActor))
	{
		return;
	}

	if (GetMainWeapon() != nullptr)
	{
		MainWeapon->Destroy();
	}
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (APawn* Pawn = Cast<APawn>(InstigatorActor))
	{
		SpawnParameters.Instigator = Pawn;
	}
	SpawnParameters.Owner = InstigatorActor;
	
	MainWeapon = GetWorld()->SpawnActor<AARPGBaseEquippable>(WeaponClass, InstigatorActor->GetTransform(), SpawnParameters);

	Cast<AARPGBaseWeapon>(MainWeapon)->OnEquipped(InstigatorActor);
	
	bIsWeaponEquipped = true;
}

void UARPGInventoryComponent::ToggleMainWeaponMontage(AActor* InstigatorActor)
{
	if (!(MainWeapon && InstigatorActor))
	{
		return;
	}
	
	if (ACharacter*	Character = Cast<ACharacter>(InstigatorActor))
	{
		if (AARPGBaseWeapon* Weapon = Cast<AARPGBaseWeapon>(MainWeapon))
		{
			if (bIsWeaponEquipped)
			{
				Character->PlayAnimMontage(Weapon->GetDisarmAnimationMontage());
				bIsWeaponEquipped = false;
			} else
			{
				Character->PlayAnimMontage(Weapon->GetDrawAnimationMontage());
				bIsWeaponEquipped = true;
			}
		}
	}
}

void UARPGInventoryComponent::PutBackWeapon()
{
	if (AARPGBaseWeapon* Weapon = Cast<AARPGBaseWeapon>(MainWeapon))
	{
		if (AActor*	Owner = GetOwner())
		{
			Weapon->OnUnequipped(Owner);
		}
	}
}

void UARPGInventoryComponent::DrawWeapon()
{
	if (AARPGBaseWeapon* Weapon = Cast<AARPGBaseWeapon>(MainWeapon))
	{
		if (AActor*	Owner = GetOwner())
		{
			Weapon->OnEquipped(Owner);
		}
	}
}

void UARPGInventoryComponent::SetMainWeapon(AARPGBaseEquippable* Weapon)
{
	MainWeapon = Weapon;
}
