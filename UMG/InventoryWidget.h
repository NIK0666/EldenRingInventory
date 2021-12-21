// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UItemEquipmentSlotWidget;

/**
 * 
 */
UCLASS()
class TESTELDENRING_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:	
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
};
