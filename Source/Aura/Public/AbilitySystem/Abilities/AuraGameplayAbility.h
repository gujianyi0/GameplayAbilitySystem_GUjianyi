// Copyright Gujianyi

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;
	
	virtual FString GetDescription(int32 Level);//获取当前等级的技能描述
	virtual FString GetNextLevelDescription(int32 Level);//获取技能下一等级的技能描述
	static FString GetLockedDescription(int32 Level);//获取锁定技能描述
	
protected:

	float GetManaCost(float InLevel = 1.f) const;
	float GetCooldown(float InLevel = 1.f) const;
};
