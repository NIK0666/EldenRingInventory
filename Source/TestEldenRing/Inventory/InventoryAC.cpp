// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryAC.h"

#include "InventoryItemSlot.h"
#include "Data/InventoryData.h"


UInventoryAC::UInventoryAC()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryAC::BeginPlay()
{
	Super::BeginPlay();	
}

UInventoryItemSlot* UInventoryAC::AddItem(const FDataTableRowHandle& ItemRow, int32 Count)
{
	FItem* Item = ItemRow.DataTable->FindRow<FItem>(ItemRow.RowName, "FItem");
	if (Item == nullptr)
	{
		//TODO Not found!
		return nullptr;
	}
	
	if (Item->IsConsumable())
	{
		const FConsumableItem* ConsumableItem = static_cast<FConsumableItem*>(Item);

		if (UInventoryItemSlot* Slot = FindInventoryItemSlot(ItemRow))
		{
			const int32 ToChest = FMath::Max(Slot->Count + Count - ConsumableItem->MaxCount, 0);
			const int32 ToInventory = Count - ToChest;
			
			if (ToChest > 0)
			{	
				MoveItemToChest.Broadcast(ItemRow, *Item, ToChest);				
			}
			
			Slot->Count += ToInventory;
			if (ToInventory > 0)
			{
				AddedItemEvent.Broadcast(ItemRow, *Item, ToInventory, Slot->Count);
			}
			
			return Slot;
		}

		const int32 ToChest = FMath::Max(Count - ConsumableItem->MaxCount, 0);
		const int32 ToInventory = Count - ToChest;
		if (ToChest > 0)
		{	
			MoveItemToChest.Broadcast(ItemRow, *Item, ToChest);				
		}
		
		UInventoryItemSlot* ItemSlot = NewObject<UInventoryItemSlot>();
		ItemSlot->ItemRow = ItemRow;
		ItemSlot->Count = ToInventory;	
		Inventory.Add(ItemSlot);
		if (ToInventory > 0)
		{
			AddedItemEvent.Broadcast(ItemRow, *Item, ToInventory, ToInventory);
		}
		return ItemSlot;
	}

	UInventoryItemSlot* ItemSlot = NewObject<UInventoryItemSlot>();
	ItemSlot->ItemRow = ItemRow;
	ItemSlot->Count = Count;	
	Inventory.Add(ItemSlot);
	AddedItemEvent.Broadcast(ItemRow, *Item, Count, Count);
	return ItemSlot;
	
}

TArray<UInventoryItemSlot*> UInventoryAC::SetItems(TArray<FInventorySlot> Items, bool bRemoveAllItems)
{
	if (bRemoveAllItems)
	{
		Inventory.Empty();
	}	
	TArray<UInventoryItemSlot*> OutItems;
	
	for (const FInventorySlot& ItemSlotStruct : Items)
	{
		OutItems.Add(AddItem(ItemSlotStruct.ItemRow, ItemSlotStruct.Count));
	}

	return OutItems;
	
}

bool UInventoryAC::RemoveItem(const FDataTableRowHandle& ItemRow, int32 Count)
{
	FItem* Item = ItemRow.DataTable->FindRow<FItem>(ItemRow.RowName, "FItem");
	if (Item == nullptr)
	{
		//TODO Not found!
		return false;
	}
	
	UInventoryItemSlot* Slot = FindInventoryItemSlot(ItemRow);
	if (Slot == nullptr)
	{
		//TODO Not found!
		return false;
	}

	if (Item->IsConsumable())
	{
		Slot->Count = FMath::Max(Slot->Count - Count, 0);

		if (Slot->Count == 0)
		{
			Inventory.Remove(Slot);
		}
	}
	else
	{
		Inventory.Remove(Slot);
	}

	if (RemovedItemEvent.IsBound())
	{
		RemovedItemEvent.Broadcast(ItemRow, *Item, Count, Slot->Count);
	}
	
	return true;
}

bool UInventoryAC::SetEquipItem(UInventoryItemSlot* InventoryItemSlot)
{	
	if (!IsValid(InventoryItemSlot))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryAC::ChangeEquipItem - Invalid InventoryItemSlot!"));
		return false;
	}

	TArray<EEquipmentSlot> EquipmentKeys;
	Equipment.GetKeys(EquipmentKeys);

	for (const EEquipmentSlot& SlotType : EquipmentKeys)
	{
		FEquipmentSlot* SlotPtr = &Equipment[SlotType];
		
		if (SlotPtr->DataTable != InventoryItemSlot->ItemRow.DataTable)
		{
			continue;
		}
		if (SlotPtr->InventoryItemSlot != nullptr)
		{
			continue;
		}
		
		UInventoryItemSlot* PrevItemSlot = SlotPtr->InventoryItemSlot;
		SlotPtr->InventoryItemSlot = InventoryItemSlot;
		SlotPtr->InventoryItemSlot->Count = InventoryItemSlot->Count;

		if (EquipItemChanged.IsBound())
		{
			EquipItemChanged.Broadcast(SlotType, PrevItemSlot, InventoryItemSlot);
		}
		return true;
	}
	return false;
}

void UInventoryAC::SetEquipItemToSlot(UInventoryItemSlot* InventoryItemSlot, EEquipmentSlot EquipmentSlot)
{
	if (Equipment.Find(EquipmentSlot) == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryAC::SetEquipItemToSlot - Slot type \"%s\" is not found!"), *UEnum::GetValueAsString(EquipmentSlot));
		return;
	}

	if (Equipment[EquipmentSlot].InventoryItemSlot == InventoryItemSlot)
	{
		return;
	}

	UInventoryItemSlot* PrevItemSlot = Equipment[EquipmentSlot].InventoryItemSlot;
	Equipment[EquipmentSlot].InventoryItemSlot = InventoryItemSlot;
	
	if (EquipItemChanged.IsBound())
	{
		EquipItemChanged.Broadcast(EquipmentSlot, PrevItemSlot, InventoryItemSlot);
	}
}

void UInventoryAC::ClearEquipSlot(EEquipmentSlot EquipmentSlot)
{
	if (Equipment.Find(EquipmentSlot) == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryAC::ClearEquipSlot - Equipment slot \"%s\" is not found!"), *UEnum::GetValueAsString(EquipmentSlot));
		return;
	}

	if (Equipment[EquipmentSlot].InventoryItemSlot != nullptr)
	{
		UInventoryItemSlot* PrevItemSlot = Equipment[EquipmentSlot].InventoryItemSlot;
		Equipment[EquipmentSlot].InventoryItemSlot = nullptr;
		
		if (EquipItemChanged.IsBound())
		{
			EquipItemChanged.Broadcast(EquipmentSlot, PrevItemSlot, nullptr);
		}
	}	
}

UInventoryItemSlot* UInventoryAC::FindInventoryItemSlot(const FDataTableRowHandle& ItemRow)
{
	for (UInventoryItemSlot* Slot : Inventory)
	{
		if (Slot->ItemRow != ItemRow)
		{
			continue;
		}
		
		return Slot;
	}
	return nullptr;
}
