// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInventorySlotWidget.h"

#include "Components/Image.h"

void UItemInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	if (!IsEmptySlot())
	{
		SetSelected();
	}	
}

FReply UItemInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetPressedButtons().Find(EKeys::LeftMouseButton))	//Only PC
	{
		if (InventoryItemStartEquipped.IsBound())
		{
			InventoryItemStartEquipped.Execute(this);
		}
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UItemInventorySlotWidget::Update(UInventoryItemSlot* InventoryItemSlot)
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

	const bool IsEquip = IsValid(InventoryItemSlot) ? InventoryItemSlot->EquipmentSlotType != EEquipmentSlot::None : false;
	
	EquipmentImage->SetVisibility(IsEquip ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UItemInventorySlotWidget::SetSelected()
{
	if (InventorySlotSelected.IsBound())
	{
		InventorySlotSelected.Execute(this);
	}
}

void UItemInventorySlotWidget::ChangeSelectionState(bool bIsSelected)
{
	SelectedImage->SetVisibility(bIsSelected ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

bool UItemInventorySlotWidget::IsEmptySlot()
{
	return ItemSlot == nullptr;
}

FText UItemInventorySlotWidget::GetItemName()
{
	if (ItemSlot == nullptr)
	{
		return FText::FromString(TEXT("-"));
	}

	return ItemSlot->GetItemInfo()->ItemName;
}

UInventoryItemSlot* UItemInventorySlotWidget::GetInventoryItemSlot()
{
	return ItemSlot;
}
