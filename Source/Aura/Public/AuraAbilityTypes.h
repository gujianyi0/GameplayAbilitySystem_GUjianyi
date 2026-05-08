#pragma once //预处理指令 确保这个头文件只被包含（include）一次，防止重复定义。

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	FDamageEffectParams(){}

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UObject> WorldContextObject = nullptr;//当前场景上下文对象

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;//需要应用的GE的类

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent;//源ASC

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent;//目标ASC

	UPROPERTY(BlueprintReadWrite)
	float BaseDamage = 0.f;//基础伤害

	UPROPERTY(BlueprintReadWrite)
	float AbilityLevel = 1.f;//技能等级

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag DamageType = FGameplayTag();//负面效果伤害类型

	UPROPERTY(BlueprintReadWrite)
	float DebuffChance = 0.f;//触发负面效果概率

	UPROPERTY(BlueprintReadWrite)
	float DebuffDamage = 0.f;//负面效果伤害

	UPROPERTY(BlueprintReadWrite)
	float DebuffDuration = 0.f;//负面效果持续时间

	UPROPERTY(BlueprintReadWrite)
	float DebuffFrequency = 0.f;//负面效果触发频率
	
	//死亡时施加的冲力大小
	UPROPERTY(BlueprintReadWrite)
	float DeathImpulseMagnitude = 0.f;
	
	//死亡时受到冲击的朝向
	UPROPERTY(BlueprintReadWrite)
	FVector DeathImpulse = FVector::ZeroVector;
	
	//攻击时施加的击退大小
	UPROPERTY(BlueprintReadWrite)
	float KnockbackForceMagnitude = 0.f;

	//击退概率
	UPROPERTY(BlueprintReadWrite)
	float KnockbackChance = 0.f;

	//攻击时受到击退的朝向
	UPROPERTY(BlueprintReadWrite)
	FVector KnockbackForce = FVector::ZeroVector;
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsRadialDamage = false;

	UPROPERTY(BlueprintReadWrite)
	float RadialDamageInnerRadius = 0.f;

	UPROPERTY(BlueprintReadWrite)
	float RadialDamageOuterRadius = 0.f;

	UPROPERTY(BlueprintReadWrite)
	FVector RadialDamageOrigin = FVector::ZeroVector;
	
};


USTRUCT(BlueprintType) //在蓝图中可作为类型使用
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()  //宏 自动生成构造函数、析构函数、拷贝构造函数等

public:

	bool IsCriticalHit() const { return bIsCriticalHit; }//获取 暴击
	bool IsBlockedHit () const { return bIsBlockedHit; }//获取 格挡
	bool IsSuccessfulDebuff() const { return bIsSuccessfulDebuff; }//获取 应用负面效果
	float GetDebuffDamage() const { return DebuffDamage; }//获取 负面效果伤害
	float GetDebuffDuration() const { return DebuffDuration; }//获取 负面效果持续时间
	float GetDebuffFrequency() const { return DebuffFrequency; }//获取 负面效果伤害触发间隔
	TSharedPtr<FGameplayTag> GetDamageType() const { return DamageType; }//获取 负面效果伤害类型
	FVector GetDeathImpulse() const { return DeathImpulse; }//获取到死亡冲击的方向和力度
	FVector GetKnockbackForce() const { return KnockbackForce; }
	bool IsRadialDamage() const { return bIsRadialDamage; }
	float GetRadialDamageInnerRadius() const { return RadialDamageInnerRadius; }
	float GetRadialDamageOuterRadius() const { return RadialDamageOuterRadius; }
	FVector GetRadialDamageOrigin() const { return RadialDamageOrigin; }
	
	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }// 设置 暴击
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }// 设置 格挡
	void SetIsSuccessfulDebuff(bool bInIsDebuff) { bIsSuccessfulDebuff = bInIsDebuff; } //设置 应用负面效果
	void SetDebuffDamage(float InDamage) { DebuffDamage = InDamage; }//设置 负面效果伤害
	void SetDebuffDuration(float InDuration) { DebuffDuration = InDuration; }//设置 负面效果伤害
	void SetDebuffFrequency(float InFrequency) { DebuffFrequency = InFrequency; }//设置 负面效果伤害
	void SetDamageType(TSharedPtr<FGameplayTag> InDamageType) { DamageType = InDamageType; };//设置 负面效果伤害类型
	void SetDeathImpulse(const FVector& InImpulse) { DeathImpulse = InImpulse; }
	void SetKnockbackForce(const FVector& InForce) { KnockbackForce = InForce; }
	void SetIsRadialDamage(bool bInIsRadialDamage) { bIsRadialDamage = bInIsRadialDamage; }
	void SetRadialDamageInnerRadius(float InRadialDamageInnerRadius) { RadialDamageInnerRadius = InRadialDamageInnerRadius; }
	void SetRadialDamageOuterRadius(float InRadialDamageOuterRadius) { RadialDamageOuterRadius = InRadialDamageOuterRadius; }
	void SetRadialDamageOrigin(const FVector& InRadialDamageOrigin) { RadialDamageOrigin = InRadialDamageOrigin; }
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
	
	UPROPERTY()
	bool bIsSuccessfulDebuff = false;

	UPROPERTY()
	float DebuffDamage = 0.f;

	UPROPERTY()
	float DebuffDuration = 0.f;

	UPROPERTY()
	float DebuffFrequency = 0.f;

	TSharedPtr<FGameplayTag> DamageType;
	
	
	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector; //死亡时受到冲击的朝向
	
	UPROPERTY()
	FVector KnockbackForce = FVector::ZeroVector;
	
	//当前伤害类型是否为范围伤害
	UPROPERTY()
	bool bIsRadialDamage = false;

	//内半径：在此半径内的所有目标都将受到完整的伤害
	UPROPERTY()
	float RadialDamageInnerRadius = 0.f;

	//外半径：超过这个距离的目标受到最小伤害，最小伤害如果设置为0，则圈外不受到伤害
	UPROPERTY()
	float RadialDamageOuterRadius = 0.f;

	//伤害源的中心点
	UPROPERTY()
	FVector RadialDamageOrigin = FVector::ZeroVector;
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