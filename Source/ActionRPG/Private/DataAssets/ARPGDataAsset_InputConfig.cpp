// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/ARPGDataAsset_InputConfig.h"

TObjectPtr<UInputAction> UARPGDataAsset_InputConfig::FindNativeInputActionByTag(
	const FGameplayTag& Tag) const
{
	for (FARPGTaggedInputAction InputActionConfig : InputActionConfigs)
	{
		if (InputActionConfig.InputTag.MatchesTagExact(Tag))
		{
			return InputActionConfig.InputAction;
		}
	}
	return nullptr;
}
