// Copyright Gujianyi


#include "AbilitySystem/Abilities/AuraFireBlast.h"

FString UAuraFireBlast::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
			// 标题
			"<Title>火焰爆发</>\n\n"

			// 技能描述
			"<Small>等级： </><Level>%d</>\n"
			// ManaCost
			"<Small>蓝量消耗： </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>技能冷却： </><Cooldown>%.1f</>\n\n"

			// Number of Fire Balls
			"<Default>向四面八方发射 %d </>"
			"<Default>颗火球，每颗火球会在返回时发生爆炸，并造成</>"

			// Damage
			"<Damage>%d</><Default>点径向火焰伤害，并有一定几率触发燃烧。</>"),

			// 动态修改值
			Level,
			ManaCost,
			Cooldown,
			NumFireBalls,
			ScaledDamage);
}

FString UAuraFireBlast::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		    //标题
			"<Small>下一级 </><Level>%d</>\n"
			
			//技能描述
			// ManaCost
			"<Small>蓝量消耗： </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>技能冷却： </><Cooldown>%.1f</>\n\n"

			// Number of Fire Balls
			"<Default>向四面八方发射 %d </>"
			"<Default>颗火球，每颗火球会在返回时发生爆炸，并造成</>"

			// Damage
			"<Damage>%d</><Default>点径向火焰伤害，并有一定几率触发燃烧。</>"),

			// 动态修改值
			Level,
			ManaCost,
			Cooldown,
			NumFireBalls,
			ScaledDamage);
}