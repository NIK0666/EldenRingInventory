// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPanelWidget.h"

#include "Components/TextBlock.h"
#include "Components/WrapBox.h"

#include "TestEldenRing/Inventory/UMG/Slots/ItemInventorySlotWidget.h"

void UInventoryPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();
	AERPlayerController* PlayerController = Cast<AERPlayerController>(GetOwningPlayer());
	if (IsValid(PlayerController))
	{
		InventoryAC = PlayerController->GetInventoryAC();
	}

	for (const auto L_ItemWidget : InventoryWrapBox->GetAllChildren())
	{
		UItemInventorySlotWidget* L_SlotWidget = Cast<UItemInventorySlotWidget>(L_ItemWidget);
		L_SlotWidget->OnSlotSelected.BindUObject(this, &UInventoryPanelWidget::SetSelectedInventorySlot);

		L_SlotWidget->OnSlotClicked.BindWeakLambda(this, [this](UBaseSlotWidget* SlotWidget)
		{
			if (OnEquipSelection.IsBound())
			{				
				OnEquipSelection.Execute();
			}
		});
	}
}

void UInventoryPanelWidget::Update(const FText& SlotNameText, EEquipmentSlot EquipmentSlot, UInventoryItemSlot* CurrentInventoryItemSlot)
{
	InventorySlotTypeText->SetText(SlotNameText);

	CurrentEquipmentItemSlot = InventoryAC->GetInventoryItemSlotByEquipmentType(EquipmentSlot);
	
	if (CurrentEquipmentItemSlot != nullptr)
	{
		Items = InventoryAC->GetInventoryItems(CurrentEquipmentItemSlot->DataTable);
	}
	else
	{
		Items.Empty();
	}
	
	SelectedEquipmentSlot = EquipmentSlot;
	
	for (int32 i = 0; i < InventoryWrapBox->GetChildrenCount(); i++)
	{
		UItemInventorySlotWidget* ItemWidget = Cast<UItemInventorySlotWidget>(InventoryWrapBox->GetChildAt(i));

		if (i < Items.Num())
		{
			ItemWidget->Update(Items[i]);
			if (CurrentInventoryItemSlot != nullptr && CurrentInventoryItemSlot == Items[i])
			{
				ItemWidget->SetSelected();
			}
		}
		else
		{
			ItemWidget->Update(nullptr);
		}		
	}

	if (Items.Num() > 0 && CurrentInventoryItemSlot == nullptr)
	{
		Cast<UItemInventorySlotWidget>(InventoryWrapBox->GetChildAt(0))->SetSelected();
	}
	
}

void UInventoryPanelWidget::SetSelectedInventorySlot(UBaseSlotWidget* NewSlotWidget)
{
	if (CurrentSelectedInventorySlotWidget)
	{
		CurrentSelectedInventorySlotWidget->ChangeSelectionState(false);
	}	
	NewSlotWidget->ChangeSelectionState(true);
	CurrentSelectedInventorySlotWidget = NewSlotWidget;

	ItemNameText->SetText(NewSlotWidget->GetItemName());
	
	if (OnChangedLookItemInfo.IsBound())
	{
		if (CurrentEquipmentItemSlot->InventoryItemSlot)
		{
			OnChangedLookItemInfo.Execute(
				NewSlotWidget->GetInventoryItemSlot()->GetItemInfo(), NewSlotWidget->GetInventoryItemSlot(),
				CurrentEquipmentItemSlot->InventoryItemSlot->GetItemInfo());
		}
		else
		{
			OnChangedLookItemInfo.Execute(
				NewSlotWidget->GetInventoryItemSlot()->GetItemInfo(), NewSlotWidget->GetInventoryItemSlot(),
				InventoryAC->GetEmptyEquipmentInfo(SelectedEquipmentSlot));
		}
		
	}
}

void UInventoryPanelWidget::EquipSelectedItem() const
{	
	InventoryAC->SetEquipItemToSlot(CurrentSelectedInventorySlotWidget->GetInventoryItemSlot(), SelectedEquipmentSlot);
}

UBaseSlotWidget* UInventoryPanelWidget::GetSelectedSlotWidget() const
{
	return CurrentSelectedInventorySlotWidget;
}

void UInventoryPanelWidget::MoveHorizontalSelection(bool bPositive) const
{
	if (CurrentSelectedInventorySlotWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryPanelWidget::MoveHorizontalSelection - SelectedSlot is NULL!"));
		return;
	}

	int32 CurrentSlotIndex = InventoryWrapBox->GetChildIndex(CurrentSelectedInventorySlotWidget);
	const int32 MaxSlotIndex = Items.Num() - 1;

	if (MaxSlotIndex <= 0 && CurrentSlotIndex == 0)
	{
		return;
	}

	if (bPositive)
	{
		CurrentSlotIndex = (CurrentSlotIndex + 1 > MaxSlotIndex) ? 0 : CurrentSlotIndex + 1;
	}
	else
	{
		CurrentSlotIndex = (CurrentSlotIndex  < 1) ? MaxSlotIndex : CurrentSlotIndex - 1;
	}

	UItemInventorySlotWidget* NewSelected = Cast<UItemInventorySlotWidget>(InventoryWrapBox->GetChildAt(CurrentSlotIndex));
	NewSelected->SetSelected();

}

void UInventoryPanelWidget::MoveVerticalSelection(bool bPositive)
{
	if (CurrentSelectedInventorySlotWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryPanelWidget::MoveHorizontalSelection - SelectedSlot is NULL!"));
		return;
	}

	int32 CurrentSlotIndex = InventoryWrapBox->GetChildIndex(CurrentSelectedInventorySlotWidget);
	const int32 MaxSlotIndex = Items.Num() - 1;

	if (MaxSlotIndex <= 0 && CurrentSlotIndex == 0)
	{
		return;
	}

	if (bPositive)
	{
		CurrentSlotIndex = (CurrentSlotIndex + 5 > MaxSlotIndex) ? CurrentSlotIndex % 5 : CurrentSlotIndex + 5;
	}
	else
	{
		if (CurrentSlotIndex < 5)
		{
			const int32 Rows = (MaxSlotIndex / 5);
			CurrentSlotIndex = (Rows * 5) + CurrentSlotIndex;
			if (CurrentSlotIndex > MaxSlotIndex)
			{
				CurrentSlotIndex -= 5;
			}			
		}
		else
		{
			CurrentSlotIndex -= 5;
		}
		
	}

	UItemInventorySlotWidget* NewSelected = Cast<UItemInventorySlotWidget>(InventoryWrapBox->GetChildAt(CurrentSlotIndex));
	NewSelected->SetSelected();	
}

void UInventoryPanelWidget::EndHidePanel()
{
	if (IsValid(CurrentSelectedInventorySlotWidget))
	{
		CurrentSelectedInventorySlotWidget->ChangeSelectionState(false);
		CurrentSelectedInventorySlotWidget = nullptr;
	}
}
