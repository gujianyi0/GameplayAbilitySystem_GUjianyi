// Copyright Gujianyi


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
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
		"<Default>发射 %d 颗火球,"
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
			"<Default>发射 %d 颗火球,"
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
	"<Default>发射 %d 颗火球,"
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
	
	const FVector Forward = Rotation.Vector();//获取朝向向量
	
	const int32 EffectiveNumProjectiles = FMath::Min(NumProjectiles, GetAbilityLevel());
	//根据函数获取到所有生成的转向
	TArray<FRotator> Rotations = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, EffectiveNumProjectiles);
	
	//遍历所有朝向，并生成火球术
	for (const FRotator& Rot : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());

		//SpawnActorDeferred将异步创建实例，在实例创建完成时，相应的数据已经应用到了实例身上
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		
		//根据目标类型设置HomingTargetComponent，此内容必须在飞弹被生成后设置
		if (HomingTarget && HomingTarget->Implements<UCombatInterface>())
		{
			//设置攻击的位置为攻击对象的根位置
			Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
			
		}
		else
		{
			//如果没有获取到攻击目标，则创建一个可销毁的并应用
			Projectile->HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
			Projectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
			Projectile->ProjectileMovement->HomingTargetComponent = Projectile->HomingTargetSceneComponent;
		}
		//设置飞弹朝向目标时的加速度
		Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::FRandRange(HomingAccelerationMin, HomingAccelerationMax);
		Projectile->ProjectileMovement->bIsHomingProjectile = bLaunchHomingProjectiles;
		
		//确保变换设置被正确应用
		Projectile->FinishSpawning(SpawnTransform);
	}
}