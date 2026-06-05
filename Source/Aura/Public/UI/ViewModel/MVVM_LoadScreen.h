// Copyright Gujianyi

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadScreen.generated.h"

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
 
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadSlot> LoadSlotViewModelClass;
 
	UFUNCTION(BlueprintPure)
	UMVVM_LoadSlot* GetLoadSlotViewModelByIndex(int32 Index) const;
 
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
  };
