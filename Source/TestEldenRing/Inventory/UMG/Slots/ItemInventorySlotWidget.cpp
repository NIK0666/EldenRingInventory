// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInventorySlotWidget.h"

#include "Components/Image.h"
#include "TestEldenRing/Inventory/InventoryItemSlot.h"
#include "TestEldenRing/Inventory/Data/InventoryData.h"

void UItemInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	if (!IsEmptySlot())
	{
		SetSelected();
	}	
}

void UItemInventorySlotWidget::Update(UInventoryItemSlot* InventoryItemSlot)
{
	Super::Update(InventoryItemSlot);

	const bool IsEquip = IsValid(InventoryItemSlot) ? InventoryItemSlot->EquipmentSlotType != EEquipmentSlot::None : false;	
	EquipmentImage->SetVisibility(IsEquip ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}