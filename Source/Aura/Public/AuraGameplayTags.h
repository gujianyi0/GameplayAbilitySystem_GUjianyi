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

	FGameplayTag Attributes_Meta_IncomingXP;//元属性经验 标签
	
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_Passive_1;//被动技能1
	FGameplayTag InputTag_Passive_2;//被动技能2
	
	FGameplayTag Damage;//伤害 标签
	FGameplayTag Damage_Fire;//火属性伤害 标签
	FGameplayTag Damage_Lightning;//雷属性伤害 标签
	FGameplayTag Damage_Arcane;//魔法伤害 标签
	FGameplayTag Damage_Physical;//物理伤害 标签
	
	FGameplayTag Attributes_Resistance_Fire;//火属性伤害抵抗 标签
	FGameplayTag Attributes_Resistance_Lightning;//雷属性伤害抵抗 标签
	FGameplayTag Attributes_Resistance_Arcane;//魔法伤害抵抗 标签
	FGameplayTag Attributes_Resistance_Physical;//物理伤害抵抗 标签
	
	FGameplayTag Debuff_Burn;//火属性负面效果 燃烧
	FGameplayTag Debuff_Stun; //雷属性负面效果 眩晕
	FGameplayTag Debuff_Arcane;//魔法伤害负面效果
	FGameplayTag Debuff_Physical;//物理伤害负面效果 流血

	FGameplayTag Debuff_Chance;//负面效果触发几率标签
	FGameplayTag Debuff_Damage;//负面效果伤害标签
	FGameplayTag Debuff_Duration;//负面效果持续时间标签
	FGameplayTag Debuff_Frequency;//负面效果触发间隔标签

	FGameplayTag Abilities_None;
	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;//召唤技能激活标签
	
	FGameplayTag Abilities_HitReact;

	FGameplayTag Abilities_Status_Locked;
	FGameplayTag Abilities_Status_Eligible;
	FGameplayTag Abilities_Status_Unlocked;
	FGameplayTag Abilities_Status_Equipped;

	FGameplayTag Abilities_Type_Offensive;
	FGameplayTag Abilities_Type_Passive;
	FGameplayTag Abilities_Type_None;
	
	FGameplayTag Abilities_Fire_FireBolt;
	FGameplayTag Abilities_Fire_FireBlast;	
	FGameplayTag Abilities_Lightning_Electrocute;//雷击技能标签
	FGameplayTag Abilities_Arcane_ArcaneShards;
	
	FGameplayTag Abilities_Passive_HaloOfProtection;
	FGameplayTag Abilities_Passive_LifeSiphon;
	FGameplayTag Abilities_Passive_ManaSiphon;

	FGameplayTag Cooldown_Fire_FireBolt;//火球术冷却标签
	
	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;

	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;
	
	FGameplayTag Montage_Attack_Weapon;//使用武器攻击蒙太奇标签
	FGameplayTag Montage_Attack_RightHand;//右手攻击蒙太奇标签
	FGameplayTag Montage_Attack_LeftHand;//左手攻击蒙太奇标签
	FGameplayTag CombatSocket_Tail;
	
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;//属性伤害标签对应属性抵抗标签
	TMap<FGameplayTag, FGameplayTag> DamageTypesToDebuffs;//属性伤害标签对应的负面标签
	
	FGameplayTag Effects_HitReact;
	
	FGameplayTag Player_Block_InputPressed;//阻挡键位按下输入
	FGameplayTag Player_Block_InputHeld;//阻挡键位悬停输入
	FGameplayTag Player_Block_InputReleased;//阻挡键位抬起输入
	FGameplayTag Player_Block_CursorTrace;//阻挡鼠标拾取事件
	
	FGameplayTag GameplayCue_FireBlast;
protected:

private:
	static FAuraGameplayTags GameplayTags;
};
