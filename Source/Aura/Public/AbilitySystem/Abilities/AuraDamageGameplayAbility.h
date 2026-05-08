// Copyright Gujianyi

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
	
	//创建技能负面效果使用的结构体
	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr) const;
	
	UFUNCTION(BlueprintPure)
	float GetDamageAtLevel() const;
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat Damage;
	
	//触发负面效果概率
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffChance = 20.f;

	//负面效果伤害
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffDamage = 5.f;
	
	//负面效果触发频率
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffFrequency = 1.f;

	//死亡时施加的冲力大小
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DeathImpulseMagnitude = 1000.f;

	//击中时施加的冲力大小
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float KnockbackForceMagnitude = 1000.f;

	//击中时触发击退的概率
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float KnockbackChance = 0.f;
	
	//负面效果持续时间
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffDuration = 5.f;
	
	//当前伤害类型是否为范围伤害
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	bool bIsRadialDamage = false;

	//内半径：在此半径内的所有目标都将受到完整的伤害
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float RadialDamageInnerRadius = 0.f;

	//外半径：超过这个距离的目标受到最小伤害，最小伤害如果设置为0，则圈外不受到伤害
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float RadialDamageOuterRadius = 0.f;

	//伤害源的中心点
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector RadialDamageOrigin = FVector::ZeroVector;

	//从角色设置的蒙太奇数组总，随机一个蒙太奇使用
	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;
	
};
