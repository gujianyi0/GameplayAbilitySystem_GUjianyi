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

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;	

	FGameplayTag Attributes_Resistance_Fire;//火属性伤害抵抗 标签
	FGameplayTag Attributes_Resistance_Lightning;//雷属性伤害抵抗 标签
	FGameplayTag Attributes_Resistance_Arcane;//魔法伤害抵抗 标签
	FGameplayTag Attributes_Resistance_Physical;//物理伤害抵抗 标签
	
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	
	FGameplayTag Damage;//伤害 标签
	FGameplayTag Damage_Fire;//火属性伤害 标签
	FGameplayTag Damage_Lightning;//雷属性伤害 标签
	FGameplayTag Damage_Arcane;//魔法伤害 标签
	FGameplayTag Damage_Physical;//物理伤害 标签
	
	FGameplayTag Abilities_Attack;
	
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;//属性伤害标签对应属性抵抗标签
	
	FGameplayTag Effects_HitReact;
	
protected:

private:
	static FAuraGameplayTags GameplayTags;
};
