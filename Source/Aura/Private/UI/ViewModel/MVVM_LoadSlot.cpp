// Copyright Gujianyi


#include "UI/ViewModel/MVVM_LoadSlot.h"

#include "UI/ViewModel/MVVM_LoadScreen.h"

void UMVVM_LoadSlot::InitializeSlot()
{
	
	SetWidgetSwitcherIndex.Broadcast(2);
}



void UMVVM_LoadSlot::SetLoadSlotName(FString InLoadSlotName)
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, InLoadSlotName);
}


