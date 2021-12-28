// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestEldenRing/Core/ERPlayerController.h"
#include "TestEldenRing/Inventory/InventoryAC.h"
#include "EquipmentPanelWidget.generated.h"

class UTextBlock;
class UVerticalBox;
class UItemEquipmentSlotWidget;
/**
 * 
 */
UCLASS()
class TESTELDENRING_API UEquipmentPanelWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void MoveHorizontalSelection(bool bPositive) const;

	UFUNCTION()
	void MoveVerticalSelection(bool bPositive) const;

	UFUNCTION()
	void EquipRemove() const;

	UFUNCTION()
	FText GetSelectedSlotName();

	UFUNCTION()
	EEquipmentSlot GetSelectedSlotType();

	DECLARE_DELEGATE(FOnEquipSelectionStart);
	FOnEquipSelectionStart OnEquipSelectionStart;
	
	DECLARE_DELEGATE_OneParam(FOnSelectedEquipSlot, UItemEquipmentSlotWidget* ItemEquipmentSlotWidget);
	FOnSelectedEquipSlot OnSelectedEquipSlot;

protected:
	
	UPROPERTY(Transient)
	UInventoryAC* InventoryAC;
		
	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotLHand1;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotLHand2;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotLHand3;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotRHand1;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotRHand2;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotRHand3;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotArrows1;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotArrows2;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotBolts1;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotBolts2;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotHelm;
	
	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotArmor;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotGloves;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotBoots;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotAmulet1;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotAmulet2;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotConsumables1;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotConsumables2;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotConsumables3;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotConsumables4;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotConsumables5;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotConsumables6;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotConsumables7;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotConsumables8;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotConsumables9;

	UPROPERTY(meta=(BindWidget))
	UItemEquipmentSlotWidget* EquipSlotConsumables10;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* EquipmentSlotsVBox;

	UPROPERTY()
	UTextBlock* SlotTypeText;

	UPROPERTY()
	UTextBlock* ItemNameText;
	
private:
	UFUNCTION()
	UItemEquipmentSlotWidget* GetItemEquipmentSlotWidget(EEquipmentSlot EquipmentSlotType) const;	

	UFUNCTION()
	void SetSelectedEquipSlot(UItemEquipmentSlotWidget* NewSelectedEquipSlot);	
	
	UFUNCTION()
	void SetItemEquipped(UItemEquipmentSlotWidget* ItemEquipmentSlotWidget) const;

	UPROPERTY(Transient)
	UItemEquipmentSlotWidget* CurrentSelectedSlotWidget;
};
