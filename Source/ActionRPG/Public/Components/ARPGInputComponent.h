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
	void BindNativeInputAction(const UARPGDataAsset_InputConfig* InputConfig,const FGameplayTag& InputTag,ETriggerEvent TriggerEvent,UserObject* ContextObject,CallbackFunc Func);

	template<class UserObject,typename CallbackFunc>
	void BindAbilityInputActions(const UARPGDataAsset_InputConfig* InputConfig,UserObject* ContextObject,CallbackFunc InputPressedFunc,CallbackFunc InputReleasedFunc);
};

template <class UserObject, typename CallbackFunc>
void UARPGInputComponent::BindNativeInputAction(const UARPGDataAsset_InputConfig* InputConfig,
	const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject,
	CallbackFunc Func)
{
	checkf(InputConfig,TEXT("Input config data asset is null, binding cancelled"));
	
	if (UInputAction* FoundAction = InputConfig->FindNativeInputActionByTag(InputTag))
	{
		BindAction(FoundAction,TriggerEvent,ContextObject,Func);
	}
}

template <class UserObject, typename CallbackFunc>
void UARPGInputComponent::BindAbilityInputActions(const UARPGDataAsset_InputConfig* InputConfig, UserObject* ContextObject,
	CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	checkf(InputConfig,TEXT("Input config data asset is null, binding cancelled"));
	
	for (const FARPGTaggedInputAction& AbilityInputActionConfig : InputConfig->AbilityTaggedInputActions)
	{
		if(!AbilityInputActionConfig.IsValid()) continue;
		
		BindAction(AbilityInputActionConfig.InputAction,ETriggerEvent::Started,ContextObject,InputPressedFunc,AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction,ETriggerEvent::Completed,ContextObject,InputReleasedFunc,AbilityInputActionConfig.InputTag);
	}
}
