// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestEldenRing/CharacterStatus/Data/CharacterStatusData.h"

#include "TestEldenRing/Inventory/Data/InventoryData.h"

#include "ItemPropertiesPanelWidget.generated.h"

class UWidgetSwitcher;
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
	
	void Update(FItem* ItemInfo, UInventoryItemSlot* InventoryItemSlot, FItem* ComparedItemInfo);
	void ChangeDetailsView(bool NewIsDetails);
	void FlipItemInfoView();

protected:
	void ShowEffectsBlock(const TArray<FItemEffect>& EffectsInfo, const FText& CaptionText) const;
	void ShowAttackPower(const FAttackPower* AttackPowerInfo, const FAttackPower* ComparedAttackPower);
	void ShowGuardedDamageNegation(const FGuardedDamageNegation* GuardedDamageNegationInfo, const FGuardedDamageNegation* ComparedGuardedDamageNegation);
	void ShowAttributeScaling(const FAttributeScaling* AttributeScalingInfo, const FAttributeScaling* ComparedAttributeScaling);
	void ShowAttributeRequired(const FAttributeRequired* AttributeRequiredInfo, const FCharacterStatus* CharacterStatus) const;
	void ShowDamageNegation(const FDamageNegation* DamageNegationInfo, const FDamageNegation* ComparedDamageNegation);
	void ShowResistance(const FResistance* ResistanceInfo, const FResistance* ComparedResistance);

	
	void SetRowValueColor(UPropertyRowWidget* RowWidget, float Value);
	
	// COMMON
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* Common;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Common_NameText;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Common_Row_0;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Common_Row_1;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Common_Row_2;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Common_Row_3;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Common_Row_4;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Common_Row_5;
	
	// DETAILED
	UPROPERTY(meta=(BindWidget))
	UImage* Details_IconImage;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Details_CaptionText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Details_DescriptionText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Details_SpellCaptionText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Details_SpellDescriptionText;

	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* ItemInfoSwitcher;	
	

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

	
	// GUARDED DAMAGE NEGATION
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* GuardedDamageNegation;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* GuardedDamageNegation_PhysicalRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* GuardedDamageNegation_MagicRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* GuardedDamageNegation_FireRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* GuardedDamageNegation_LightningRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* GuardedDamageNegation_HolyRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* GuardedDamageNegation_GuardBoostRow;
	

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
	

	// EFFECTS
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* Effects;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Effects_CaptionText;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Effects_Row_0;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Effects_Row_1;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Effects_Row_2;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* Effects_Row_3;

	//COLORS
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FSlateColor PositiveColor;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FSlateColor NegativeColor;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FSlateColor NormalColor;
	
private:	
	bool IsDetails = false;
};
