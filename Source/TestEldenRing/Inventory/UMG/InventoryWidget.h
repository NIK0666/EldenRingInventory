// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SNodePanel.h"

#include "Blueprint/UserWidget.h"

#include "InventoryWidget.generated.h"

class UItemPropertiesWidget;
class UCanvasPanel;
class UInventoryPanelWidget;
class UEquipmentPanelWidget;

UENUM()
enum class EInventoryUIState
{
	Equipment,
	SelectItem,
	Animated	
};
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

protected:
	UPROPERTY(meta=(BindWidget))
	UEquipmentPanelWidget* EquipmentPanel;

	UPROPERTY(meta=(BindWidget))
	UInventoryPanelWidget* InventoryPanel;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* SimpleViewPanel;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* DetailedViewPanel;

	UPROPERTY(meta=(BindWidget))
	UItemPropertiesWidget* ItemProperties;

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* EquipmentToInventoryPanelAnim;

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* InventoryToEquipmentPanelAnim;

	// UPROPERTY()
	// UInventoryAC* InventoryAC;

private:
	UFUNCTION()
	static bool CheckIsPressedActionKey(const FName& ActionName, const FKey& PressedKey);

	void EquipSelectionStart();
	void EquipSelectionCancel();

	void InventorySelectionStart();
	void SimpleViewChange();
	
	EInventoryUIState InventoryUIState = EInventoryUIState::Equipment;

	bool bIsSimpleView = false;
};
