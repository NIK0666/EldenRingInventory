// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "BaseSlotWidget.h"

#include "ItemInventorySlotWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class TESTELDENRING_API UItemInventorySlotWidget : public UBaseSlotWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;	

	virtual void Update(UInventoryItemSlot* InventoryItemSlot) override;

protected:	
	UPROPERTY(meta=(BindWidget))
	UImage* EquipmentImage;
};
