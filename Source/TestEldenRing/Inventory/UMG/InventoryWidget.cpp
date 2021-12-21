// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "EquipmentPanelWidget.h"
#include "InventoryPanelWidget.h"
#include "ItemEquipmentSlotWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/InputSettings.h"
#include "TestEldenRing/Core/ERPlayerController.h"
#include "TestEldenRing/Inventory/InventoryAC.h"

bool UInventoryWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (!IsValid(EquipmentPanel))
	{
		return false;
	}

	if (!IsValid(InventoryPanel))
	{
		return false;
	}
	
	return true;
}

FReply UInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (bIsEquipmentShow)
	{
		if (CheckIsPressedActionKey(FName("UI_Left"), InKeyEvent.GetKey()))
		{
			EquipmentPanel->MoveHorizontalSelection(false);
		}
		else if (CheckIsPressedActionKey(FName("UI_Right"), InKeyEvent.GetKey()))
		{
			EquipmentPanel->MoveHorizontalSelection(true);
		}
		else if (CheckIsPressedActionKey(FName("UI_Up"), InKeyEvent.GetKey()))
		{
			EquipmentPanel->MoveVerticalSelection(false);
		}
		else if (CheckIsPressedActionKey(FName("UI_Down"), InKeyEvent.GetKey()))
		{
			EquipmentPanel->MoveVerticalSelection(true);
		}
		else if (CheckIsPressedActionKey(FName("UI_EquipRemove"), InKeyEvent.GetKey()))
		{
			UE_LOG(LogTemp, Log, TEXT("UI_REMOVE: %s"), *InKeyEvent.GetKey().ToString());
			EquipmentPanel->EquipRemove();
		}
	}	
	
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

bool UInventoryWidget::CheckIsPressedActionKey(const FName& ActionName, const FKey& PressedKey)
{
	if (UInputSettings* InputSettings = UInputSettings::GetInputSettings())
	{
		TArray<FInputActionKeyMapping> OutMappings;
		InputSettings->GetActionMappingByName(ActionName, OutMappings);

		for (const FInputActionKeyMapping& OutMapping : OutMappings)			
		{
			if (OutMapping.Key == PressedKey)
			{
				return true;
			}
		}
	}
	return false;
}