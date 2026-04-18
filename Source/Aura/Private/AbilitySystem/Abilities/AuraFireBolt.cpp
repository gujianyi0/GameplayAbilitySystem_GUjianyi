// Copyright Gujianyi


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "Aura/Public/AuraGameplayTags.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
		// 标题
		"<Title>FIRE BOLT</>\n\n"

		// 细节
		"<Small>等级： </><Level>%d</>\n"
		"<Small>技能冷却： </><ManaCost>%.1f</>\n"
		"<Small>蓝量消耗： </><Cooldown>%.1f</>\n\n"//%.1f会四舍五入到小数点后一位

		// 技能描述
		"<Default>发射 %d 级火球,"
		"在发生撞击时产生爆炸，并造成 </>"

		// Damage
		"<Damage>%d</><Default> 点火焰伤害，"
		"并有一定几率燃烧。</>"),

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
			"<Title>FIRE BOLT</>\n\n"

			// 细节
			"<Small>等级： </><Level>%d</>\n"
			"<Small>技能冷却： </><ManaCost>%.1f</>\n"
			"<Small>蓝量消耗： </><Cooldown>%.1f</>\n\n"//%.1f会四舍五入到小数点后一位

			// 技能描述
			"<Default>发射 %d 级火球,"
			"在发生撞击时产生爆炸，并造成 </>"

			// Damage
			"<Damage>%d</><Default> 点火焰伤害，"
			"并有一定几率燃烧。</>"),

			// 动态修改值
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			ScaledDamage);
		
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
	// 标题
	"<Title>FIRE BOLT</>\n\n"

	// 细节
	"<Small>等级： </><Level>%d</>\n"
	"<Small>技能冷却： </><ManaCost>%.1f</>\n"
	"<Small>蓝量消耗： </><Cooldown>%.1f</>\n\n"//%.1f会四舍五入到小数点后一位

	// 技能描述
	"<Default>发射 %d 级火球,"
	"在发生撞击时产生爆炸，并造成 </>"

	// Damage
	"<Damage>%d</><Default> 点火焰伤害，"
	"并有一定几率燃烧。</>"),

	// 动态修改值
	Level,
	ManaCost,
	Cooldown,
	FMath::Min(Level, NumProjectiles),
	ScaledDamage);
		
}
