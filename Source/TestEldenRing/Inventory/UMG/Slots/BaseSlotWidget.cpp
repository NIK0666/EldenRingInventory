// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSlotWidget.h"

#include "Components/Image.h"
#include "TestEldenRing/Inventory/InventoryItemSlot.h"

bool UBaseSlotWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (!IsValid(ItemImage))
	{
		return false;
	}

	if (!IsValid(SelectedImage))
	{
		return false;
	}

	return true;
}

FReply UBaseSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetPressedButtons().Contains(EKeys::LeftMouseButton))
	{
		if (OnSlotClicked.IsBound())
		{
			OnSlotClicked.Execute(this);
		}
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UBaseSlotWidget::Update(UInventoryItemSlot* InventoryItemSlot)
{
	ItemSlot = InventoryItemSlot;

	if (IsValid(InventoryItemSlot))
	{
		ItemImage->SetVisibility(ESlateVisibility::Visible);
		ItemImage->SetBrushFromTexture(InventoryItemSlot->GetItemInfo()->Icon);
	}
	else
	{
		ItemImage->SetVisibility(ESlateVisibility::Collapsed);
	}	
}

void UBaseSlotWidget::SetSelected()
{
	if (OnSlotSelected.IsBound())
	{
		OnSlotSelected.Execute(this);
	}
}

void UBaseSlotWidget::ChangeSelectionState(bool bIsSelected) const
{
	SelectedImage->SetVisibility(bIsSelected ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

bool UBaseSlotWidget::IsEmptySlot() const
{
	return ItemSlot == nullptr;
}

UInventoryItemSlot* UBaseSlotWidget::GetInventoryItemSlot() const
{
	return ItemSlot;
}

FText UBaseSlotWidget::GetItemName() const
{
	if (ItemSlot == nullptr)
	{
		return FText::FromString(TEXT("-"));
	}

	return ItemSlot->GetItemInfo()->ItemName;
}
