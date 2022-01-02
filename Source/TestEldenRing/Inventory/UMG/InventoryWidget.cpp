// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/CanvasPanel.h"
#include "GameFramework/InputSettings.h"

#include "Panels/ItemPropertiesPanelWidget.h"
#include "Panels/InventoryPanelWidget.h"
#include "Slots/ItemInventorySlotWidget.h"

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

	EquipmentPanel->OnEquipSelectionStart.BindWeakLambda(this, [this]()
	{
		EquipSelectionStart();
	});

	InventoryPanel->OnEquipSelection.BindWeakLambda(this, [this]()
	{
		InventorySelectionStart();
	});

	EquipmentPanel->OnChangedLookItemInfo.BindWeakLambda(this, [this](FItem* ItemInfo, UInventoryItemSlot* InventoryItemSlot, FItem* ComparedItemInfo)
	{
		ItemProperties->Update(ItemInfo, InventoryItemSlot, ComparedItemInfo);
	});
	
	InventoryPanel->OnChangedLookItemInfo.BindWeakLambda(this, [this](FItem* ItemInfo, UInventoryItemSlot* InventoryItemSlot, FItem* ComparedItemInfo)
	{
		ItemProperties->Update(ItemInfo, InventoryItemSlot, ComparedItemInfo);
	});
	
	return true;
}

FReply UInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{

	if (CheckIsPressedActionKey(FName("UI_SimpleViewChange"), InKeyEvent.GetKey()))
	{
		SimpleViewChange();
	}
	else if (InventoryUIState == EInventoryUIState::Equipment)
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
			EquipmentPanel->EquipRemove();
		}
		else if (CheckIsPressedActionKey(FName("UI_EquipSelect"), InKeyEvent.GetKey()))
		{
			EquipSelectionStart();			
		}		
	}
	else if (InventoryUIState == EInventoryUIState::SelectItem)
	{
		if (CheckIsPressedActionKey(FName("UI_Left"), InKeyEvent.GetKey()))
		{
			InventoryPanel->MoveHorizontalSelection(false);
		}
		else if (CheckIsPressedActionKey(FName("UI_Right"), InKeyEvent.GetKey()))
		{
			InventoryPanel->MoveHorizontalSelection(true);
		}
		else if (CheckIsPressedActionKey(FName("UI_Up"), InKeyEvent.GetKey()))
		{
			InventoryPanel->MoveVerticalSelection(false);
		}
		else if (CheckIsPressedActionKey(FName("UI_Down"), InKeyEvent.GetKey()))
		{
			InventoryPanel->MoveVerticalSelection(true);
		}
		else if (CheckIsPressedActionKey(FName("UI_InventoryBack"), InKeyEvent.GetKey()))
		{
			EquipSelectionCancel();
		}
		else if (CheckIsPressedActionKey(FName("UI_InventorySelect"), InKeyEvent.GetKey()))
		{
			UE_LOG(LogTemp, Log, TEXT("UI_SELECT: %s"), *InKeyEvent.GetKey().ToString());
			InventorySelectionStart();			
		}
		else if (CheckIsPressedActionKey(FName("UI_ItemInfo"), InKeyEvent.GetKey()))
		{
			ShowItemInfoDetails();
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

void UInventoryWidget::EquipSelectionStart()
{
	PlayAnimation(EquipmentToInventoryPanelAnim);
	FTimerHandle Handle;
	InventoryUIState = EInventoryUIState::Animated;
	
	InventoryPanel->Update(EquipmentPanel->GetSelectedSlotName(), EquipmentPanel->GetSelectedSlotType());
	
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateWeakLambda(this, [this]()
	{
		InventoryUIState = EInventoryUIState::SelectItem;
	}), EquipmentToInventoryPanelAnim->GetEndTime(), false);

}

void UInventoryWidget::EquipSelectionCancel()
{
	PlayAnimation(InventoryToEquipmentPanelAnim);
	FTimerHandle Handle;
	InventoryUIState = EInventoryUIState::Animated;
	ItemProperties->ChangeDetailsView(false);	
	EquipmentPanel->ChangedLookItemInfo();
	
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateWeakLambda(this, [this]()
	{
		InventoryPanel->EndHidePanel();
		InventoryUIState = EInventoryUIState::Equipment;
	}), EquipmentToInventoryPanelAnim->GetEndTime(), false);
}

void UInventoryWidget::InventorySelectionStart()
{
	if (!IsValid(InventoryPanel->GetSelectedSlotWidget()) || InventoryPanel->GetSelectedSlotWidget()->IsEmptySlot())
	{
		return;
	}
	
	PlayAnimation(InventoryToEquipmentPanelAnim);
	FTimerHandle Handle;
	InventoryUIState = EInventoryUIState::Animated;
	
	InventoryPanel->EquipSelectedItem();
	ItemProperties->ChangeDetailsView(false);
	
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateWeakLambda(this, [this]()
	{
		InventoryPanel->EndHidePanel();
		InventoryUIState = EInventoryUIState::Equipment;
	}), EquipmentToInventoryPanelAnim->GetEndTime(), false);
}

void UInventoryWidget::SimpleViewChange()
{
	bIsSimpleView = !bIsSimpleView;
	SimpleViewPanel->SetVisibility(bIsSimpleView ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	DetailedViewPanel->SetVisibility(!bIsSimpleView ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UInventoryWidget::ShowItemInfoDetails()
{
	ItemProperties->FlipItemInfoView();
}

