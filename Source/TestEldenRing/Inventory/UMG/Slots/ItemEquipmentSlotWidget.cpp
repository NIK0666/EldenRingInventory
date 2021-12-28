// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEquipmentSlotWidget.h"

#include "Components/Image.h"

bool UItemEquipmentSlotWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	if (!IsValid(PlaceholderImage))
	{
		return false;
	}

	PlaceholderImage->SetBrush(PlaceholderBrush);

	return true;	
}

void UItemEquipmentSlotWidget::SetSelected()
{
	if (SlotSelected.IsBound())
	{
		SlotSelected.Execute(this);
	}
}

void UItemEquipmentSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	SetSelected();
}

FReply UItemEquipmentSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetPressedButtons().Find(EKeys::LeftMouseButton))
	{
		if (ItemEquipped.IsBound())
		{
			ItemEquipped.Execute(this);
		}
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UItemEquipmentSlotWidget::Update(UInventoryItemSlot* InventoryItemSlot)
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

UInventoryItemSlot* UItemEquipmentSlotWidget::GetInventoryItemSlot()
{	
	return ItemSlot;
}
void UItemEquipmentSlotWidget::ChangeSelectionState(bool bIsSelected)
{
	SelectedImage->SetVisibility(bIsSelected ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

bool UItemEquipmentSlotWidget::IsEmptySlot()
{
	return ItemSlot == nullptr;
}

FText UItemEquipmentSlotWidget::GetItemName()
{
	if (ItemSlot == nullptr)
	{
		return FText::FromString(TEXT("-"));
	}

	return ItemSlot->GetItemInfo()->ItemName;
}

FText UItemEquipmentSlotWidget::GetSlotName()
{
	return SlotName;
}
