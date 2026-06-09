// Copyright Gujianyi

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadSlot.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, WidgetSwitcherIndex);

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
	
	void InitializeSlot();
	
	void SetLoadSlotName(FString InLoadSlotName);
	FString GetLoadSlotName() const { return LoadSlotName; };

	UPROPERTY()
	FString PlayerName;
	

	UPROPERTY()
	FString SlotIndex;
	

private:
	
	//用户控件的名称
	UPROPERTY(EditAnywhere,BlueprintReadWrite,FieldNotify, Setter, Getter, meta=(AllowPrivateAccess="true"))
	FString LoadSlotName;
	
};
