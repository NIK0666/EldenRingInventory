// Fill out your copyright notice in the Description page of Project Settings.


#include "ERPlayerController.h"

#include "TestEldenRing/Inventory/InventoryAC.h"
#include "TestEldenRing/CharacterStatus/CharacterStatusAC.h"

AERPlayerController::AERPlayerController(const FObjectInitializer &ObjectInitializer)
{
	InventoryAC = ObjectInitializer.CreateDefaultSubobject<UInventoryAC>(this, FName(TEXT("InventoryAC")));
	CharacterStatusAC = ObjectInitializer.CreateDefaultSubobject<UCharacterStatusAC>(this, FName(TEXT("CharacterStatusAC")));
}

void AERPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	InventoryAC->RemovedItemEvent.AddWeakLambda(this,
		[this](const FDataTableRowHandle& ItemRow, const FItem& Item, int32 RemovedCount, int32 TotalCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("Removed Item: %s; Count: %d, Total: %d"), *Item.ItemName.ToString(), RemovedCount, TotalCount);
	});

	InventoryAC->EquipItemChanged.AddWeakLambda(this,
		[this](EEquipmentSlot EquipmentSlot, UInventoryItemSlot* FromInventoryItemSlot, UInventoryItemSlot* ToInventoryItemSlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("Equip item changed!"));
	});

	InventoryAC->AddedItemEvent.AddWeakLambda(this,
		[this](const FDataTableRowHandle& ItemRow, const FItem& Item, int32 AddedCount, int32 TotalCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("Added Item: %s; Count: %d, Total: %d"), *Item.ItemName.ToString(), AddedCount, TotalCount);
	});
	
	InventoryAC->MoveItemToChest.AddWeakLambda(this,
		[this](const FDataTableRowHandle& ItemRow, const FItem& Item, int32 Count)
	{
		UE_LOG(LogTemp, Error, TEXT("Moved to Chest: %s; Count: %d"), *Item.ItemName.ToString(), Count);
	});
	
}

void AERPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

UInventoryAC* AERPlayerController::GetInventoryAC() const
{
	return InventoryAC;
}

UCharacterStatusAC* AERPlayerController::GetCharacterStatusAC() const
{
	return CharacterStatusAC;
}
