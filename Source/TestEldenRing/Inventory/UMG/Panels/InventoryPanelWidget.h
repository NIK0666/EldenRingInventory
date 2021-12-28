// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "EquipmentPanelWidget.h"

#include "InventoryPanelWidget.generated.h"

class UItemInventorySlotWidget;
class UWrapBox;
class USubcategoriesPanelWidget;
/**
 * 
 */
UCLASS()
class TESTELDENRING_API UInventoryPanelWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void Update(const FText& SlotNameText, EEquipmentSlot EquipmentSlot);

	UFUNCTION()
	void SetSelectedInventorySlot(UItemInventorySlotWidget* NewSelectedInventorySlot);

	UFUNCTION()
	void EquipSelectedItem() const;
	
	UFUNCTION()
	UItemInventorySlotWidget* GetSelectedSlotWidget();
	
	void MoveHorizontalSelection(bool bPositive);
	
	void MoveVerticalSelection(bool bPositive);
	
	void EndHidePanel();

	DECLARE_DELEGATE(FOnEquipSelection);
	FOnEquipSelection OnEquipSelection;	
	
	DECLARE_DELEGATE_OneParam(FOnChangedCurrentItemSlot, const UInventoryItemSlot* InventoryItemSlot);
	FOnChangedCurrentItemSlot OnChangedCurrentItemSlot;

protected:	
	UPROPERTY(Transient)
	UInventoryAC* InventoryAC;
	
	UPROPERTY(meta=(BindWidget))
	USubcategoriesPanelWidget* SubcategoriesPanel;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* InventorySlotTypeText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemNameText;
	
	UPROPERTY(meta=(BindWidget))
	UWrapBox* InventoryWrapBox;
	
	TArray<UInventoryItemSlot*> Items;	

private:
	
	UPROPERTY(Transient)
	EEquipmentSlot SelectedEquipmentSlot;
	
	UPROPERTY(Transient)
	UItemInventorySlotWidget* CurrentSelectedInventorySlotWidget;
};
