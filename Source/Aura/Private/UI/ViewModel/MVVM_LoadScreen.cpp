// Copyright Gujianyi


#include "UI/ViewModel/MVVM_LoadScreen.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ViewModel/MVVM_LoadSlot.h"

 void UMVVM_LoadScreen::InitializeLoadSlots()
  {
  	LoadSlot_0 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
 	LoadSlot_0->SetLoadSlotName("LoadSlot_0");
  	LoadSlots.Add(0, LoadSlot_0);
  	LoadSlot_1 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
 	LoadSlot_1->SetLoadSlotName("LoadSlot_1");
  	LoadSlots.Add(1, LoadSlot_1);
  	LoadSlot_2 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
 	LoadSlot_2->SetLoadSlotName("LoadSlot_2");
  	LoadSlots.Add(2, LoadSlot_2);
  }

UMVVM_LoadSlot* UMVVM_LoadScreen::GetLoadSlotViewModelByIndex(int32 Index) const
{
	return LoadSlots.FindChecked(Index);
}

void UMVVM_LoadScreen::NewSlotButtonPressed(int32 Slot, const FString& EnteredName)
{
 	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
 	
 	LoadSlots[Slot]->SetPlayerName(EnteredName);
 	LoadSlots[Slot]->SlotStatus = Taken;
 	AuraGameMode->SaveSlotData(LoadSlots[Slot], Slot);
 	LoadSlots[Slot]->InitializeSlot();
}

void UMVVM_LoadScreen::NewGameButtonPressed(int32 Slot)
{
	LoadSlots[Slot]->SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadScreen::SelectSlotButtonPressed(int32 Slot)
{
	
}

void UMVVM_LoadScreen::LoadData()
{
 	//获取到加载存档界面的GameMode
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
 	//遍历映射，获取对应存档
	for (const TTuple<int32, UMVVM_LoadSlot*> LoadSlot : LoadSlots)
	{
		ULoadScreenSaveGame* SaveObject = AuraGameMode->GetSaveSlotData(LoadSlot.Value->GetLoadSlotName(), LoadSlot.Key);
		//获取存档数据
		const FString PlayerName = SaveObject->PlayerName;
		TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = SaveObject->SaveSlotStatus;
		
		//设置存档视图模型数据
		LoadSlot.Value->SlotStatus = SaveSlotStatus;
		LoadSlot.Value->SetPlayerName(PlayerName);
		
		//调用视图模型初始化
		LoadSlot.Value->InitializeSlot();
	}
}