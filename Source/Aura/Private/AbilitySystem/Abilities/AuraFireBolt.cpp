// Copyright Gujianyi


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "Kismet/KismetSystemLibrary.h"
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


void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();//判断此函数是否在服务器运行
	if (!bIsServer) return;

	//获取释放位置
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(),SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();//将方向转为旋转
	if (bOverridePitch) Rotation.Pitch = PitchOverride;//覆写发射角度
	
	const FVector Forward = Rotation.Vector();
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2.f, FVector::UpVector);//获取到最左侧的角度
	const FVector RightOfSpread = Forward.RotateAngleAxis(ProjectileSpread / 2.f, FVector::UpVector);//获取到最右侧的角度
	

	//限制产生火球的最大数量
	//NumProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());
	
	//根据可生成数量进行逻辑判断
	if (NumProjectiles > 1)
	{
		
		const float DeltaSpread = ProjectileSpread / (NumProjectiles - 1);//技能分的段数
		for (int32 i = 0; i < NumProjectiles; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			const FVector Start = SocketLocation + FVector(0,0,5);
			UKismetSystemLibrary::DrawDebugArrow(
				GetAvatarActorFromActorInfo(),
				Start,
				Start + Direction * 75.f,
				1,
				FLinearColor::Red,
				120,
				1);
		}
	}
	else
	{
		// Single projectile
		const FVector Start = SocketLocation + FVector(0,0,5);
		UKismetSystemLibrary::DrawDebugArrow(
				GetAvatarActorFromActorInfo(),
				Start,
				Start + Forward * 75.f,
				1,
				FLinearColor::Red,
				120,
				1);
	}

	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + Forward * 100.f, 1, FLinearColor::White, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + LeftOfSpread * 100.f, 1, FLinearColor::Gray, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + RightOfSpread * 100.f, 1, FLinearColor::Gray, 120, 1);
}