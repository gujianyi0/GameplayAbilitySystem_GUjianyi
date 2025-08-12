// Copyright Gujianyi

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 *
 * 包含原生Gameplay标签的单例
 */

struct  FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get()
	{
		return GameplayTags ;
	}
	static void InitializeNativeGameplayTags();

protected:

private:
	static FAuraGameplayTags GameplayTags;
};
