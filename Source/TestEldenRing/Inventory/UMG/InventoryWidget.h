// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "TestEldenRing/Core/ERPlayerController.h"
#include "TestEldenRing/Inventory/InventoryAC.h"
#include "TestEldenRing/Inventory/Data/InventoryData.h"

#include "InventoryWidget.generated.h"

class UTextBlock;
class UVerticalBox;
class UItemEquipmentSlotWidget;

/**
 * 
 */
UCLASS(BlueprintType)
class TESTELDENRING_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual void NativeConstruct() override;

	UFUNCTION()
	UItemEquipmentSlotWidget* GetItemEquipmentSlotWidget(EEquipmentSlot EquipmentSlotType) const;

protected:

	UFUNCTION()
	void SetSelectedEquipSlot(UItemEquipmentSlotWidget* NewSelectedEquipSlot);
	
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
	UInventoryAC* InventoryAC;

	UPROPERTY()
	UTextBlock* SlotTypeText;

	UPROPERTY()
	UTextBlock* ItemNameText;

private:
	UPROPERTY(Transient)
	UItemEquipmentSlotWidget* CurrentSelectedSlotWidget;

	UFUNCTION()
	static bool CheckIsPressedActionKey(const FName& ActionName, const FKey& PressedKey);

	UFUNCTION()
	void MoveHorizontalSelection(bool bPositive) const;

	UFUNCTION()
	void MoveVerticalSelection(bool bPositive) const;

	UFUNCTION()
	void EquipRemove() const;
};
