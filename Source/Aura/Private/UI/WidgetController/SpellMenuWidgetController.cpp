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