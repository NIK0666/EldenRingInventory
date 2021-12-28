// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestEldenRing/Inventory/Data/InventoryData.h"
#include "ItemPropertiesWidget.generated.h"

class UTextBlock;
class UImage;
class UCanvasPanel;
class UPropertyRowWidget;
class UInventoryItemSlot;
/**
 * 
 */
UCLASS()
class TESTELDENRING_API UItemPropertiesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Update(FItem* ItemInfo);

protected:

	// COMMON
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* Common;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Common_NameText;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Common_ItemTypeRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Common_DamageTypeRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Common_SuperAttackNameRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Common_FPCostRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Common_WeightRow;
	

	// ICON BLOCK
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* IconBlock;
	
	UPROPERTY(meta=(BindWidget))
	UImage* IconBlock_IconImage;


	// ATTACK POWER
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* AttackPower;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttackPower_PhysicalRow;
	
	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttackPower_MagicRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttackPower_FireRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttackPower_LightningRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttackPower_HolyRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttackPower_CriticalRow;
	

	// DAMAGE NEGATION
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* DamageNegation;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* DamageNegation_PhysicalRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* DamageNegation_VSStrikeRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* DamageNegation_VSSlashRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* DamageNegation_VSPierceRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* DamageNegation_MagicRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* DamageNegation_FireRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* DamageNegation_LightningRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* DamageNegation_HolyRow;


	// RESISTANCE
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* Resistance;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Resistance_ImmunityRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Resistance_RobustnessRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Resistance_FocusRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Resistance_DeathRow;


	// ATTRIBUTE SCALING
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* AttributeScaling;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttributeScaling_Str_Row;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttributeScaling_Dex_Row;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttributeScaling_Int_Row;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttributeScaling_Fai_Row;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttributeScaling_Arc_Row;
	
	
	// ATTRIBUTE REQUIRED
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* AttributeRequired;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttributeRequired_Str_Row;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttributeRequired_Dex_Row;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttributeRequired_Int_Row;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttributeRequired_Fai_Row;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* AttributeRequired_Arc_Row;
};
