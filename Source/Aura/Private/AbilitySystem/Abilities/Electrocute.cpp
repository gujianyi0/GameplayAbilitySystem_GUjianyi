// Copyright Gujianyi


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>ELECTROCUTE</>\n\n"

			// 细节
			"<Small>等级： </><Level>%d</>\n"
			"<Small>技能冷却： </><ManaCost>%.1f</>\n"
			"<Small>蓝量消耗： </><Cooldown>%.1f</>\n\n"//%.1f会四舍五入到小数点后一位
			
			// 技能描述
			"<Default>使用闪电攻击敌人，并在命中敌人后，向外扩散闪电链，造成 </>"

			// Damage
			"<Damage>%d</><Default>点雷电伤害，在技能结束时对敌人造成"
			"眩晕效果</>"),
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>ELECTROCUTE</>\n\n"

			// 细节
			"<Small>等级： </><Level>%d</>\n"
			"<Small>技能冷却： </><ManaCost>%.1f</>\n"
			"<Small>蓝量消耗： </><Cooldown>%.1f</>\n\n"//%.1f会四舍五入到小数点后一位
			
			// 技能描述
			"<Default>使用闪电攻击敌人，并在命中敌人后，向外扩散 %d 条闪电链，造成 </>"

			// Damage
			"<Damage>%d</><Default>点雷电伤害，在技能结束时对敌人造成"
			"眩晕效果</>"),

			// 动态修改值
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumShockTargets - 1),
			ScaledDamage);		
	}
}

FString UElectrocute::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
	// Title
	"<Title>ELECTROCUTE</>\n\n"
	
	// 细节
	"<Small>等级： </><Level>%d</>\n"
	"<Small>技能冷却： </><ManaCost>%.1f</>\n"
	"<Small>蓝量消耗： </><Cooldown>%.1f</>\n\n"//%.1f会四舍五入到小数点后一位
	
	// 技能描述
	"<Default>使用闪电攻击敌人，并在命中敌人后，向外扩散%d条闪电链，造成 </>"

	// Damage
	"<Damage>%d</><Default>点雷电伤害，在技能结束时对敌人造成"
	"眩晕效果</>"),
	Level,
	ManaCost,
	Cooldown,
	FMath::Min(Level, MaxNumShockTargets - 1),
	ScaledDamage);

}