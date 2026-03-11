#pragma once //预处理指令 确保这个头文件只被包含（include）一次，防止重复定义。

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

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

	/** 用于序列化类的参数 */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
	
protected:

	UPROPERTY()
	bool bIsBlockedHit = false; //格挡
	
	UPROPERTY()
	bool bIsCriticalHit = false;  //暴击
	
};