// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "InventoryWidget.generated.h"

class UInventoryPanelWidget;
class UEquipmentPanelWidget;

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

	// UPROPERTY()
	// UInventoryAC* InventoryAC;

private:
	UFUNCTION()
	static bool CheckIsPressedActionKey(const FName& ActionName, const FKey& PressedKey);

	bool bIsEquipmentShow = true;
};
