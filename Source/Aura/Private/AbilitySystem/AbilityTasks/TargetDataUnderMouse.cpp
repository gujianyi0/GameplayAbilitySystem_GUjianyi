// Copyright Gujianyi


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{

	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (!bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		//we are on the server, so listen for target data.
	}

	

}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	//创建一个预测窗口，该窗口允许客户端在不确定服务器响应的情况下，对游戏状态进行预测性更新。
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	//获取鼠标拾取结果
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	//创建需要上传服务器端的TargetData
	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	//创建TargetData句柄，上传到服务器端需要上传句柄
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);

	FGameplayTag ApplicationTag;
	//将TargetData上传至服务器端
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	//判断服务器端是否通过验证
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
