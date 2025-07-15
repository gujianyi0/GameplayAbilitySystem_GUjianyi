
// Copyright Gujianyi


#include "UI/HUD/AuraHUD.h"
#include  "UI/Widget/AuraUserWidget.h"//添加以避免“类型不完整”错误

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	Widget->AddToViewport();
}
