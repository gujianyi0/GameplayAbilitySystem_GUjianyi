// Copyright Gujianyi


#include "AbilitySystem/Abilities/ArcaneShards.h"

FString UArcaneShards::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
		// 标题
		"<Title>ARCANE SHARDS</>\n"

		// 细节
		"<Small>等级：</> <Level>%d</>\n"
		"<Small>技能冷却：</> <Cooldown>%.1f</>\n"
		"<Small>蓝量消耗：</> <ManaCost>%.1f</>\n\n"//%.1f会四舍五入到小数点后一位
		// 技能描述
		"<Default>首次激活技能使用魔法光圈划定攻击位置，再次释放在魔法光圈位置生成奥术碎片，攻击附近敌人，造成</>"
		// Damage
		"<Damage>%d</><Default>点奥术伤害。</>"),

		// 动态修改值
		Level,
		ManaCost,
		Cooldown,
		ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
		// 标题
		"<Title>ARCANE SHARDS</>\n"

		// 细节
		"<Small>等级：</> <Level>%d</>\n"
		"<Small>技能冷却：</> <Cooldown>%.1f</>\n"
		"<Small>蓝量消耗：</> <ManaCost>%.1f</>\n\n"//%.1f会四舍五入到小数点后一位
		// 技能描述
		"<Default>首次激活技能使用魔法光圈划定攻击位置，再次释放在魔法光圈位置生成%d奥术碎片，攻击附近敌人，造成</>"
		// Damage
		"<Damage>%d</><Default>点奥术伤害。</>"),

		// 动态修改值
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxNumShards),
		ScaledDamage);
	}
}

FString UArcaneShards::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	
	return FString::Printf(TEXT(
	// 标题
	"<Title>ARCANE SHARDS</>\n"

	// 细节
	"<Small>等级：</> <Level>%d</>\n"
	"<Small>技能冷却：</> <Cooldown>%.1f</>\n"
	"<Small>蓝量消耗：</> <ManaCost>%.1f</>\n\n"//%.1f会四舍五入到小数点后一位
	// 技能描述
	"<Default>首次激活技能使用魔法光圈划定攻击位置，再次释放在魔法光圈位置生成%d奥术碎片，攻击附近敌人，造成</>"
	// Damage
	"<Damage>%d</><Default>点奥术伤害。</>"),

	// 动态修改值
	Level,
	ManaCost,
	Cooldown,
	FMath::Min(Level, MaxNumShards),
	ScaledDamage);
}