// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "TestEldenRing/Inventory/InventoryItemSlot.h"
#include "BaseSlotWidget.h"

#include "ItemEquipmentSlotWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS(BlueprintType)
class TESTELDENRING_API UItemEquipmentSlotWidget : public UBaseSlotWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	FText GetSlotName();

	UPROPERTY(EditInstanceOnly)
	EEquipmentSlot EquipmentSlotType;

protected:
	UPROPERTY(meta=(BindWidget))
	UImage* PlaceholderImage;

	UPROPERTY(EditInstanceOnly)
	FSlateBrush PlaceholderBrush;

	UPROPERTY(EditInstanceOnly)
	FText SlotName;
};

