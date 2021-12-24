// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestEldenRing/Inventory/Data/InventoryData.h"
#include "ItemPropertiesWidget.generated.h"

class UInventoryItemSlot;
/**
 * 
 */
UCLASS()
class TESTELDENRING_API UItemPropertiesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Update(EEquipmentSlot EquipmentSlotType, const UInventoryItemSlot* InventoryItemSlot);
};
