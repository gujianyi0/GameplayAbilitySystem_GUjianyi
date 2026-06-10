// Copyright Gujianyi

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlotSelected);

class UMVVM_LoadSlot;
/**
 * 
 */
UCLASS()
class AURA_API UMVVM_LoadScreen : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
 public:
	
	void InitializeLoadSlots();
	
	UPROPERTY(BlueprintAssignable)
	FSlotSelected SlotSelected;
	
	//每个存档插槽使用的MVVM类
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadSlot> LoadSlotViewModelClass;
 
	UFUNCTION(BlueprintPure)
	UMVVM_LoadSlot* GetLoadSlotViewModelByIndex(int32 Index) const;
 
	//创建新存档按下事件
 	UFUNCTION(BlueprintCallable)
 	void NewSlotButtonPressed(int32 Slot, const FString& EnteredName);
 
	//开始新游戏按下事件
 	UFUNCTION(BlueprintCallable)
 	void NewGameButtonPressed(int32 Slot);
 
	//选择存档按下事件
 	UFUNCTION(BlueprintCallable)
 	void SelectSlotButtonPressed(int32 Slot);
 	
	void LoadData();
	
	void SetNumLoadSlots(int32 InNumLoadSlots);
	
	int32 GetNumLoadSlots() const {return NumLoadSlots;}
 private:
	
	//索引和对应MVVM实例的映射
 	UPROPERTY()
 	TMap<int32, UMVVM_LoadSlot*> LoadSlots;
 
	//对象对MVVM实例的引用，防止垃圾回收机制对其进行回收
	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_0;
	
	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_1;
 
	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_2;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,FieldNotify, Setter, Getter, meta=(AllowPrivateAccess="true"));
	int32 NumLoadSlots;
  };
