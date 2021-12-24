// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestEldenRing/Inventory/InventoryItemSlot.h"
#include "ItemInventorySlotWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class TESTELDENRING_API UItemInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	void Update(UInventoryItemSlot* InventoryItemSlot);

	UFUNCTION()
	void SetSelected();

	UFUNCTION()
	void ChangeSelectionState(bool bIsSelected);

	UFUNCTION()
	bool IsEmptySlot();

	UFUNCTION()
	FText GetItemName();


	DECLARE_DELEGATE_OneParam(FInventorySlotSelected, UItemInventorySlotWidget* ItemInventorySlotWidget);
	FInventorySlotSelected InventorySlotSelected;
	
	UPROPERTY()
	UInventoryItemSlot* ItemSlot;

protected:
	UPROPERTY(meta=(BindWidget))
	UImage* ItemImage;
	
	UPROPERTY(meta=(BindWidget))
	UImage* SelectedImage;
	
	UPROPERTY(meta=(BindWidget))
	UImage* EquipmentImage;
};
