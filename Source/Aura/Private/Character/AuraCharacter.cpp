// Copyright Gujianyi


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"


AAuraCharacter::AAuraCharacter()
{
	//运动系统调整
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);//旋转至运动方向的速率
	GetCharacterMovement()->bConstrainToPlane = true;//运动将限制在一个平面
	GetCharacterMovement()->bSnapToPlaneAtStart = true;//运动开始时与平面对齐

	//不使用控制器的旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationYaw = false;
}
