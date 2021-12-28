// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseSlotWidget.generated.h"

class UImage;
class UInventoryItemSlot;
/**
 * 
 */
UCLASS()
class TESTELDENRING_API UBaseSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;	
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	virtual void Update(UInventoryItemSlot* InventoryItemSlot);

	UFUNCTION()
	void SetSelected();

	UFUNCTION()
	virtual void ChangeSelectionState(bool bIsSelected) const;

	UFUNCTION()
	bool IsEmptySlot() const;

	UFUNCTION()
	FText GetItemName() const;

	UFUNCTION()
	UInventoryItemSlot* GetInventoryItemSlot() const;
	

	DECLARE_DELEGATE_OneParam(FOnSlotSelected, UBaseSlotWidget* SlotWidget);
	FOnSlotSelected OnSlotSelected;

	DECLARE_DELEGATE_OneParam(FOnSlotClicked, UBaseSlotWidget* SlotWidget);
	FOnSlotClicked OnSlotClicked;

protected:
	UPROPERTY(meta=(BindWidget))
	UImage* ItemImage;
	
	UPROPERTY(meta=(BindWidget))
	UImage* SelectedImage;

	UPROPERTY()
	UInventoryItemSlot* ItemSlot;
};
