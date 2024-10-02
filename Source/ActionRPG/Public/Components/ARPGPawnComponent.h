// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARPGPawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API UARPGPawnComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	template <class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T,APawn>::Value, "T must be a subclass of APawn");
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T,AController>::Value, "T must be a subclass of AController");
		return GetOwningPawn()->GetController<T>();
	}
		
};
