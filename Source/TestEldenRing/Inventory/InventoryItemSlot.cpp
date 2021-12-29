// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemSlot.h"

FItem* UInventoryItemSlot::GetItemInfo()
{
	return ItemRow.DataTable->FindRow<FItem>(ItemRow.RowName, "FItem");
}