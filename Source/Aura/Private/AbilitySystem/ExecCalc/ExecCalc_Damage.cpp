// Copyright Gujianyi


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

//这里结构体不加F是因为它是内部结构体，不需要外部获取，也不需要在蓝图中使用
struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	AuraDamageStatics()
	{
		//参数：1.属性集 2.属性名 3.目标还是自身 4.是否设置快照（true为创建时获取，false为应用时获取）
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//获取ASC
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	
	//获取AvatarActor
	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	
	//获取挂载此类的GE实例
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	
	//设置评估参数
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	//获取护甲
	float Armor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters,Armor);
	Armor = FMath::Max<float>(0.f, Armor);
	++Armor;
	
	//输出计算结果
	const FGameplayModifierEvaluatedData EvaluatedData(DamageStatics().ArmorProperty,EGameplayModOp::Additive,Armor);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
