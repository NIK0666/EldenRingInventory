// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestEldenRing/Inventory/InventoryItemSlot.h"
#include "ItemEquipmentSlotWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS(BlueprintType)
class TESTELDENRING_API UItemEquipmentSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	UFUNCTION()
	void SetSelected();
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
		
	UFUNCTION()
	void Update(UInventoryItemSlot* InventoryItemSlot);

	UFUNCTION()
	void ChangeSelectionState(bool bIsSelected);

	UFUNCTION()
	bool IsEmptySlot();

	UFUNCTION()
	FText GetItemName();

	UFUNCTION()
	FText GetSlotName();

	UPROPERTY(EditInstanceOnly)
	EEquipmentSlot EquipmentSlotType;

	DECLARE_DELEGATE_OneParam(FSlotSelected, UItemEquipmentSlotWidget* ItemEquipmentSlotWidget);
	FSlotSelected SlotSelected;	

protected:
	UPROPERTY(meta=(BindWidget))
	UImage* ItemImage;
	
	UPROPERTY(meta=(BindWidget))
	UImage* SelectedImage;
	
	UPROPERTY(meta=(BindWidget))
	UImage* PlaceholderImage;

	UPROPERTY()
	UInventoryItemSlot* ItemSlot;

	UPROPERTY(EditInstanceOnly)
	FSlateBrush PlaceholderBrush;

	UPROPERTY(EditInstanceOnly)
	FText SlotName;
};

