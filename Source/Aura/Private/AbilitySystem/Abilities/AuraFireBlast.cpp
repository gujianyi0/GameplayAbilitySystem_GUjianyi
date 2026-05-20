// Copyright Gujianyi


#include "AbilitySystem/Abilities/AuraFireBlast.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraFireBall.h"

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


TArray<AAuraFireBall*> UAuraFireBlast::SpawnFireBalls()
{
	TArray<AAuraFireBall*> FireBalls;
	//获取到角色朝向和位置
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	//通过函数获取到每个需要生成的火球的旋转
	TArray<FRotator> Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumFireBalls);

	for (const FRotator& Rotator : Rotators)//生成所需的火球数组
	{
		//创建变换
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());
		
		//创建火球 使用 SpawnActorDeferred 来生成对象时，UE 会延迟实际的对象生成过程，这样你有机会在完全初始化对象之前进行自定义配置。
		AAuraFireBall* FireBall = GetWorld()->SpawnActorDeferred<AAuraFireBall>(
			FireBallClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		//设置火球的伤害配置
		FireBall->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

		FireBalls.Add(FireBall);
		
		//在配置完成火球配置后，调用FinishSpawning将火球正式添加到场景中
		FireBall->FinishSpawning(SpawnTransform);
	}
	
	return FireBalls;
}