// Copyright Gujianyi


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"


AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);//设置组件用于在网络上复制
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	SetNetUpdateFrequency(100.f);//设置服务端将此对象每秒更新的次数
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//定义在多人游戏中，需要在网络中复制的属性，当属性发生变化，修改将被发送到其它客户端和服务器
	DOREPLIFETIME(AAuraPlayerState,Level);
	DOREPLIFETIME(AAuraPlayerState, XP);
	
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::SetLevel(int32 InLevel)
{
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}
void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level);//上面修改委托只会在服务器触发，在此处设置是在服务器更新到客户端本地后触发
}

void AAuraPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);//上面修改委托只会在服务器触发，在此处设置是在服务器更新到客户端本地后触发
}
