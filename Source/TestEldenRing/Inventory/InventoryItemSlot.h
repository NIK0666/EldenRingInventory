// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/InventoryData.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"

#include "InventoryItemSlot.generated.h"

UCLASS(BlueprintType)
class TESTELDENRING_API UInventoryItemSlot : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle ItemRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count = 1;

	UPROPERTY()
	EEquipmentSlot EquipmentSlotType = EEquipmentSlot::None;

	FItem* GetItemInfo();
};

/**
 * Inventory slot struct
 */
USTRUCT(BlueprintType)
struct TESTELDENRING_API FInventorySlot
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle ItemRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count = 1;
};