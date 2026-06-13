// Copyright Gujianyi

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Game/LoadScreenSaveGame.h"
#include "MVVM_LoadSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, WidgetSwitcherIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnableSelectSlotButton, bool, bEnable);

/**
 * 
 */
UCLASS()
class AURA_API UMVVM_LoadSlot : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:

	//切换存档显示的用户控件的委托
	UPROPERTY(BlueprintAssignable)
	FSetWidgetSwitcherIndex SetWidgetSwitcherIndex;
	
	UPROPERTY(BlueprintAssignable)
	FEnableSelectSlotButton EnableSelectSlotButton;
	
	void InitializeSlot(); 
	

	
	//当前视图模型的索引，对应存档的索引
	UPROPERTY()
	int32 SlotIndex;
	
	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SlotStatus;
	
	/** Field Notifies */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter);
	FString PlayerName;

	void SetPlayerName(FString InPlayerName);
	void SetLoadSlotName(FString InLoadSlotName);
	FString GetPlayerName() const { return PlayerName; }
	FString GetLoadSlotName() const { return LoadSlotName; };

private:
	
	//用户控件的名称
	UPROPERTY(EditAnywhere,BlueprintReadWrite,FieldNotify, Setter, Getter, meta=(AllowPrivateAccess="true"))
	FString LoadSlotName;
	
};
