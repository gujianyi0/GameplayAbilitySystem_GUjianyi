#pragma once //预处理指令 确保这个头文件只被包含（include）一次，防止重复定义。

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	FDamageEffectParams(){}

	UPROPERTY()
	TObjectPtr<UObject> WorldContextObject = nullptr;//当前场景上下文对象

	UPROPERTY()
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;//需要应用的GE的类

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent;//源ASC

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent;//目标ASC

	UPROPERTY()
	float BaseDamage = 0.f;//基础伤害

	UPROPERTY()
	float AbilityLevel = 1.f;//技能等级

	UPROPERTY()
	FGameplayTag DamageType = FGameplayTag();//负面效果伤害类型

	UPROPERTY()
	float DebuffChance = 0.f;//触发负面效果概率

	UPROPERTY()
	float DebuffDamage = 0.f;//负面效果伤害

	UPROPERTY()
	float DebuffDuration = 0.f;//负面效果持续时间

	UPROPERTY()
	float DebuffFrequency = 0.f;//负面效果触发频率
};


USTRUCT(BlueprintType) //在蓝图中可作为类型使用
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()  //宏 自动生成构造函数、析构函数、拷贝构造函数等

public:

	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsBlockedHit () const { return bIsBlockedHit; }

	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	
	/** 返回用于序列化的实际结构体 */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}
	
	
	/** 创建一个副本，用于后续网络复制或者后续修改  */
	virtual FGameplayEffectContext* Duplicate() const
	{
		FGameplayEffectContext* NewContext = new FGameplayEffectContext();
		*NewContext = *this;//WithCopy 设置为true，就可以通过赋值操作进行拷贝
		if (GetHitResult())
		{
			// 深拷贝 hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}


	/** 用于序列化类的参数 */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
	
protected:

	UPROPERTY()
	bool bIsBlockedHit = false; //格挡
	
	UPROPERTY()
	bool bIsCriticalHit = false;  //暴击
	
};

template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
	{
		enum
		{
			WithNetSerializer = true,
			WithCopy = true // Necessary so that TSharedPtr<FHitResult> Data is copied around
		};
	};