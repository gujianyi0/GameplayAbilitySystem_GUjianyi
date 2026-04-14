// Copyright Gujianyi


#include "UI/WidgetController/SpellMenuWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	
	SpellPointsChanged.Broadcast(GetAuraPS()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetAuraASC()->AbilityStatusChanged.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag)
{
	if (AbilityInfo)
	{
		FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
		Info.StatusTag = StatusTag;
		AbilityInfoDelegate.Broadcast(Info);
	}
});
	
	//绑定技能点变动回调
	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda([this](int32 SpellPoints)
	{
		SpellPointsChanged.Broadcast(SpellPoints); //广播拥有的技能点
	});
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();	
	const int32 SpellPoints = GetAuraPS()->GetSpellPoints();//获取技能点数
	FGameplayTag AbilityStatus;	
	
	const bool bTagValid = AbilityTag.IsValid(); //判断传入的标签是否存在
	const bool bTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None); //判断传入的是否为空技能标签
	const FGameplayAbilitySpec* AbilitySpec = GetAuraASC()->GetSpecFromAbilityTag(AbilityTag);//通过技能标签获取技能
	const bool bSpecValid = AbilitySpec != nullptr;//判断技能实例是否存在
	if (!bTagValid || bTagNone || !bSpecValid)
	{
		//传入标签不存在，或传入的为空技能标签，或者技能实例不存在时，设置为技能按钮显示上锁状态
		AbilityStatus = GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		//从技能实例获取技能的状态标签
		AbilityStatus = GetAuraASC()->GetStatusFromSpec(*AbilitySpec);
	}

	bool bEnableSpendPoints = false;//技能是否可以升级
	bool bEnableEquip = false;//技能是否可以装配
	ShouldEnableButtons(AbilityStatus, SpellPoints, bEnableSpendPoints, bEnableEquip);//获取结果
	SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquip);//广播状态
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

	bShouldEnableSpellPointsButton = false;
	bShouldEnableEquipButton = false;
	if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped))
	{
		bShouldEnableEquipButton = true;
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bShouldEnableEquipButton = true;
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}
	}
}