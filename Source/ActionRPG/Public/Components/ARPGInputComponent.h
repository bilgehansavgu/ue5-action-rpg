// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/ARPGDataAsset_InputConfig.h"
#include "ARPGInputComponent.generated.h"

UCLASS()
class ACTIONRPG_API UARPGInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UARPGDataAsset_InputConfig* InInputConfig,const FGameplayTag& InInputTag,ETriggerEvent TriggerEvent,UserObject* ContextObject,CallbackFunc Func);
};

template <class UserObject, typename CallbackFunc>
void UARPGInputComponent::BindNativeInputAction(const UARPGDataAsset_InputConfig* InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject,
	CallbackFunc Func)
{
	checkf(InInputConfig,TEXT("Input config data asset is null, binding failed"));
	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction,TriggerEvent,ContextObject,Func);
	}
}
