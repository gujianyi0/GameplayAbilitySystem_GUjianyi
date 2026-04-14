
// Copyright Gujianyi

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class ULevelUpInfo;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*NewValue*/);
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;//覆盖虚函数获取asc
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }//获取as
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;//设置升级相关数据

	FOnPlayerStatChanged OnXPChangedDelegate;//经验值变动委托
	FOnPlayerStatChanged OnLevelChangedDelegate;//等级变动委托
	FOnPlayerStatChanged OnAttributePointsChangedDelegate;
	FOnPlayerStatChanged OnSpellPointsChangedDelegate;

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }//获取角色等级
	FORCEINLINE int32 GetXP() const { return XP; }
	FORCEINLINE int32 GetAttributePoints() const { return AttributePoints; }
	FORCEINLINE int32 GetSpellPoints() const { return SpellPoints; }

	void AddToXP(int32 InXP);//增加经验值
	void AddToLevel(int32 InLevel); //增加等级
	void AddToAttributePoints(int32 InPoints);//增加属性点
	void AddToSpellPoints(int32 InPoints);
	
	void SetXP(int32 InXP);//增加经验值
	void SetLevel(int32 InLevel);//设置当前等级
	
protected:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_XP)
	int32 XP = 1;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_AttributePoints)
	int32 AttributePoints = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_SpellPoints)
	int32 SpellPoints = 0;
	
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);//服务器出现更改自动同步到本地函数 等级
	
	UFUNCTION()
	void OnRep_XP(int32 OldXP);//服务器出现更改自动同步到本地函数 经验值
	
	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints);//服务器出现更改自动同步到本地函数 属性点

	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints);
};