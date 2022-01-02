// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPropertiesPanelWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "TestEldenRing/Inventory/InventoryItemSlot.h"

#include "TestEldenRing/Inventory/UMG/PropertyRowWidget.h"


void UItemPropertiesWidget::Update(FItem* ItemInfo, UInventoryItemSlot* InventoryItemSlot, FItem* ComparedItemInfo)
{
	
	Common->SetVisibility(ESlateVisibility::Visible);
	
	AttackPower->SetVisibility(ESlateVisibility::Collapsed);
	DamageNegation->SetVisibility(ESlateVisibility::Collapsed);
	GuardedDamageNegation->SetVisibility(ESlateVisibility::Collapsed);
	AttributeScaling->SetVisibility(ESlateVisibility::Collapsed);
	AttributeRequired->SetVisibility(ESlateVisibility::Collapsed);
	Resistance->SetVisibility(ESlateVisibility::Collapsed);
	Effects->SetVisibility(ESlateVisibility::Collapsed);
	Details_SpellCaptionText->SetVisibility(ESlateVisibility::Collapsed);
	Details_SpellDescriptionText->SetVisibility(ESlateVisibility::Collapsed);
	
	Common_Row_0->Clear();
	Common_Row_1->Clear();
	Common_Row_2->Clear();
	Common_Row_3->Clear();
	Common_Row_4->Clear();
	Common_Row_5->Clear();

	Common_NameText->SetText(ItemInfo->ItemName);

	Details_CaptionText->SetText(ItemInfo->DetailsTitle);
	Details_DescriptionText->SetText(ItemInfo->DetailsDescription);
	
	
	if (ItemInfo->Icon != nullptr)
	{
		IconBlock_IconImage->SetVisibility(ESlateVisibility::Visible);
		IconBlock_IconImage->SetBrushFromTexture(ItemInfo->Icon);

		Details_IconImage->SetVisibility(ESlateVisibility::Visible);
		Details_IconImage->SetBrushFromTexture(ItemInfo->Icon);
	}
	else
	{
		IconBlock_IconImage->SetVisibility(ESlateVisibility::Collapsed);
		Details_IconImage->SetVisibility(ESlateVisibility::Collapsed);
	}

	switch (ItemInfo->ItemType())
	{
	case EItemType::Weapon:
		{			
			AttackPower->SetVisibility(ESlateVisibility::Visible);
			GuardedDamageNegation->SetVisibility(ESlateVisibility::Visible);
			AttributeScaling->SetVisibility(ESlateVisibility::Visible);
			AttributeRequired->SetVisibility(ESlateVisibility::Visible);
			
			FWeaponItem* WeaponItem = static_cast<FWeaponItem*>(ItemInfo);

			FWeaponItem* ComparedWeaponItem = nullptr;
			if (ComparedItemInfo)
			{
				ComparedWeaponItem = static_cast<FWeaponItem*>(ComparedItemInfo);
			}
			
			Common_Row_0->SetEnumCaption(StaticEnum<EWeaponSubtype>(), static_cast<uint8>(WeaponItem->WeaponSubtype));			
			Common_Row_1->SetEnumCaption(StaticEnum<EDamageType>(), static_cast<uint8>(WeaponItem->DamageType));			
			Common_Row_3->SetCaption(WeaponItem->SuperAttack.AttackName);
			Common_Row_4->SetCaption(FText::FromString("FP Cost"));
			Common_Row_4->SetFloatValue(WeaponItem->SuperAttack.FPCost);
			Common_Row_5->SetCaption(FText::FromString("Weight"));
			Common_Row_5->SetFloatValue(WeaponItem->Weight);
			
			Details_SpellCaptionText->SetVisibility(ESlateVisibility::Visible);
			Details_SpellCaptionText->SetText(WeaponItem->SuperAttack.AttackName);
			
			Details_SpellDescriptionText->SetVisibility(ESlateVisibility::Visible);
			Details_SpellDescriptionText->SetText(WeaponItem->SuperAttack.AttackDescription);
			
			Common_Row_0->SetValueColor(NormalColor);
			Common_Row_1->SetValueColor(NormalColor);
			Common_Row_3->SetValueColor(NormalColor);

			if (ComparedWeaponItem)
			{				
				SetRowValueColor(Common_Row_4, WeaponItem->SuperAttack.FPCost - ComparedWeaponItem->SuperAttack.FPCost);
				SetRowValueColor(Common_Row_5, WeaponItem->Weight - ComparedWeaponItem->Weight);

				ShowAttackPower(&WeaponItem->AttackPower, &ComparedWeaponItem->AttackPower);
				ShowGuardedDamageNegation(&WeaponItem->GuardedDamageNegation, &ComparedWeaponItem->GuardedDamageNegation);
				ShowAttributeScaling(&WeaponItem->AttributeScaling, &ComparedWeaponItem->AttributeScaling);
				ShowAttributeRequired(&WeaponItem->AttributeRequired, &ComparedWeaponItem->AttributeRequired);
				
			}
			else
			{
				Common_Row_4->SetValueColor(NormalColor);
				Common_Row_5->SetValueColor(NormalColor);

				ShowAttackPower(&WeaponItem->AttackPower, nullptr);
				ShowGuardedDamageNegation(&WeaponItem->GuardedDamageNegation, nullptr);
				ShowAttributeScaling(&WeaponItem->AttributeScaling, nullptr);
				ShowAttributeRequired(&WeaponItem->AttributeRequired, nullptr );
			}

			if (WeaponItem != nullptr)
			{
				ShowEffectsBlock(WeaponItem->PassiveEffects, FText::FromString("Passive Effects"));	
			}

			
		}		
		break;
	case EItemType::Armor:
		{
			DamageNegation->SetVisibility(ESlateVisibility::Visible);
			Resistance->SetVisibility(ESlateVisibility::Visible);

			FArmorItem* ArmorItem = static_cast<FArmorItem*>(ItemInfo);
			
			FArmorItem* ComparedArmorItem = nullptr;
			if (ComparedItemInfo)
			{
				ComparedArmorItem = static_cast<FArmorItem*>(ComparedItemInfo);
			}

			Common_Row_5->SetCaption(FText::FromString("Weight"));
			Common_Row_5->SetFloatValue(ArmorItem->Weight);

			if (ComparedArmorItem)
			{				
				SetRowValueColor(Common_Row_5, ArmorItem->Weight - ComparedItemInfo->Weight);
			}
			else
			{
				Common_Row_5->SetValueColor(NormalColor);
			}

			ShowDamageNegation(&ArmorItem->DamageNegation, ComparedArmorItem ? &ComparedArmorItem->DamageNegation : nullptr);
			ShowResistance(&ArmorItem->Resistance, ComparedArmorItem ? &ComparedArmorItem->Resistance : nullptr);
		}
		break;
	case EItemType::Arrows:
		{
			AttackPower->SetVisibility(ESlateVisibility::Visible);
			Effects->SetVisibility(ESlateVisibility::Visible);			

			FArrowsItem* ArrowsItem = static_cast<FArrowsItem*>(ItemInfo);

			FArrowsItem* ComparedArrowsItem = nullptr;
			if (ComparedArrowsItem)
			{
				ComparedArrowsItem = static_cast<FArrowsItem*>(ComparedItemInfo);
			}

			Common_Row_0->SetCaption(FText::FromString("Arrow"));			
			Common_Row_1->SetEnumCaption(StaticEnum<EDamageType>(), static_cast<uint8>(ArrowsItem->DamageType));			
			Common_Row_2->SetCaption(FText::FromString("No. Held"));
			Common_Row_3->SetCaption(FText::FromString("Stored"));
			if (InventoryItemSlot)
			{
				Common_Row_2->SetStringValue(FString::FromInt(InventoryItemSlot->Count) + " /   " +  FString::FromInt(ArrowsItem->MaxCount));
				Common_Row_3->SetStringValue(FString::FromInt(0/*TODO Количество в сундуке*/) + " / " +  FString::FromInt(ArrowsItem->MaxStoredCount));
			}
			else
			{
				Common_Row_2->SetStringValue("- /   -");
				Common_Row_3->SetStringValue("- /   -");
			}

			Common_Row_0->SetValueColor(NormalColor);
			Common_Row_1->SetValueColor(NormalColor);
			Common_Row_2->SetValueColor(NormalColor);
			Common_Row_3->SetValueColor(NormalColor);
			
			ShowAttackPower(&ArrowsItem->AttackPower, ComparedArrowsItem ? &ComparedArrowsItem->AttackPower : nullptr);
			ShowEffectsBlock(ArrowsItem->PassiveEffects, FText::FromString("Passive Effects"));
		}
		break;
	// case EItemType::Bolts:
	// 	break;
	case EItemType::Amulet:
		{
			Effects->SetVisibility(ESlateVisibility::Visible);

			FAmuletItem* AmuletItem = static_cast<FAmuletItem*>(ItemInfo);

			FAmuletItem* ComparedAmuletItem = nullptr;
			if (ComparedAmuletItem)
			{
				ComparedAmuletItem = static_cast<FAmuletItem*>(ComparedItemInfo);
			}

			Common_Row_5->SetCaption(FText::FromString("Weight"));
			Common_Row_5->SetFloatValue(AmuletItem->Weight);

			if (ComparedAmuletItem)
			{				
				SetRowValueColor(Common_Row_5, AmuletItem->Weight - ComparedItemInfo->Weight);
			}
			else
			{
				Common_Row_5->SetValueColor(NormalColor);
			}

			ShowEffectsBlock(AmuletItem->ItemEffects, FText::FromString("Item Effect"));
		}
		break;
	case EItemType::Consumable:
		{
			Effects->SetVisibility(ESlateVisibility::Visible);

			FConsumableItem* ConsumableItem = static_cast<FConsumableItem*>(ItemInfo);

			Common_Row_0->SetCaption(FText::FromString("Consumable")); //TODO Придумать как отображать нескончаемые

			Common_Row_2->SetCaption(FText::FromString("No. Held"));
			Common_Row_3->SetCaption(FText::FromString("Stored"));
			if (InventoryItemSlot)
			{
				Common_Row_2->SetStringValue(FString::FromInt(InventoryItemSlot->Count) + " /   " +  FString::FromInt(ConsumableItem->MaxCount));
				Common_Row_3->SetStringValue(FString::FromInt(0/*TODO Количество в сундуке*/) + " / " +  FString::FromInt(ConsumableItem->MaxStoredCount));
			}
			else
			{
				Common_Row_2->SetStringValue("- /   -");
				Common_Row_3->SetStringValue("- /   -");
			}

			Common_Row_4->SetCaption(FText::FromString("FP Cost"));
			Common_Row_4->SetFloatValue(ConsumableItem->FPCost);

			Common_Row_0->SetValueColor(NormalColor);
			Common_Row_2->SetValueColor(NormalColor);
			Common_Row_3->SetValueColor(NormalColor);
			Common_Row_4->SetValueColor(NormalColor);

			ShowEffectsBlock(ConsumableItem->ItemEffects, FText::FromString("Item Effect"));
		}
		break;
	default: ;
	}
}

void UItemPropertiesWidget::ChangeDetailsView(bool NewIsDetails)
{
	IsDetails = NewIsDetails;
	ItemInfoSwitcher->SetActiveWidgetIndex(IsDetails ? 1 : 0);
}

void UItemPropertiesWidget::FlipItemInfoView()
{
	ChangeDetailsView(!IsDetails);
}

void UItemPropertiesWidget::ShowEffectsBlock(const TArray<FItemEffect>& EffectsInfo, const FText& CaptionText) const
{
	Effects->SetVisibility(ESlateVisibility::Visible);	

	Effects_Row_1->SetVisibility(EffectsInfo.Num() > 1 ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	Effects_Row_2->SetVisibility(EffectsInfo.Num() > 2 ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	Effects_Row_3->SetVisibility(EffectsInfo.Num() > 3 ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	switch (EffectsInfo.Num())
	{
	case 0:
		Effects_Row_0->SetCaption(FText::FromString("-"));
		break;
	case 4:
		Effects_Row_3->SetEnumCaption(StaticEnum<EItemEffectType>(), static_cast<int64>(EffectsInfo[3].EffectType));				
	case 3:
		Effects_Row_2->SetEnumCaption(StaticEnum<EItemEffectType>(), static_cast<int64>(EffectsInfo[2].EffectType));	
	case 2:
		Effects_Row_1->SetEnumCaption(StaticEnum<EItemEffectType>(), static_cast<int64>(EffectsInfo[1].EffectType));	
	case 1:
		Effects_Row_0->SetEnumCaption(StaticEnum<EItemEffectType>(), static_cast<int64>(EffectsInfo[0].EffectType));	
		break;
	default: break;
	}
}

void UItemPropertiesWidget::ShowAttackPower(const FAttackPower* AttackPowerInfo, const FAttackPower* ComparedAttackPower)
{
	AttackPower->SetVisibility(ESlateVisibility::Visible);
	
	AttackPower_PhysicalRow->SetIntValue(AttackPowerInfo->Physical);
	AttackPower_MagicRow->SetIntValue(AttackPowerInfo->Magic);
	AttackPower_FireRow->SetIntValue(AttackPowerInfo->Fire);
	AttackPower_LightningRow->SetIntValue(AttackPowerInfo->Lightning);
	AttackPower_HolyRow->SetIntValue(AttackPowerInfo->Holy);

	if (ComparedAttackPower)
	{
		SetRowValueColor(AttackPower_PhysicalRow, AttackPowerInfo->Physical - ComparedAttackPower->Physical);
		SetRowValueColor(AttackPower_MagicRow, AttackPowerInfo->Magic - ComparedAttackPower->Magic);
		SetRowValueColor(AttackPower_FireRow, AttackPowerInfo->Fire - ComparedAttackPower->Fire);
		SetRowValueColor(AttackPower_LightningRow, AttackPowerInfo->Lightning - ComparedAttackPower->Lightning);
		SetRowValueColor(AttackPower_HolyRow, AttackPowerInfo->Holy - ComparedAttackPower->Holy);
	}
	else
	{		
		AttackPower_PhysicalRow->SetValueColor(NormalColor);
		AttackPower_MagicRow->SetValueColor(NormalColor);
		AttackPower_FireRow->SetValueColor(NormalColor);
		AttackPower_LightningRow->SetValueColor(NormalColor);
		AttackPower_HolyRow->SetValueColor(NormalColor);
	}
}	

void UItemPropertiesWidget::ShowGuardedDamageNegation(const FGuardedDamageNegation* GuardedDamageNegationInfo, const FGuardedDamageNegation* ComparedGuardedDamageNegation)
{
	GuardedDamageNegation->SetVisibility(ESlateVisibility::Visible);
	
	GuardedDamageNegation_PhysicalRow->SetFloatValue(GuardedDamageNegationInfo->Physical);
	GuardedDamageNegation_MagicRow->SetFloatValue(GuardedDamageNegationInfo->Magic);
	GuardedDamageNegation_FireRow->SetFloatValue(GuardedDamageNegationInfo->Fire);
	GuardedDamageNegation_LightningRow->SetFloatValue(GuardedDamageNegationInfo->Lightning);
	GuardedDamageNegation_HolyRow->SetFloatValue(GuardedDamageNegationInfo->Holy);
	GuardedDamageNegation_GuardBoostRow->SetIntValue(GuardedDamageNegationInfo->GuardBoost);
	
	if (ComparedGuardedDamageNegation)
	{
		SetRowValueColor(GuardedDamageNegation_PhysicalRow, GuardedDamageNegationInfo->Physical - ComparedGuardedDamageNegation->Physical);
		SetRowValueColor(GuardedDamageNegation_MagicRow, GuardedDamageNegationInfo->Magic - ComparedGuardedDamageNegation->Magic);
		SetRowValueColor(GuardedDamageNegation_FireRow, GuardedDamageNegationInfo->Fire - ComparedGuardedDamageNegation->Fire);
		SetRowValueColor(GuardedDamageNegation_LightningRow, GuardedDamageNegationInfo->Lightning - ComparedGuardedDamageNegation->Lightning);
		SetRowValueColor(GuardedDamageNegation_HolyRow, GuardedDamageNegationInfo->Holy - ComparedGuardedDamageNegation->Holy);
		SetRowValueColor(GuardedDamageNegation_GuardBoostRow, GuardedDamageNegationInfo->GuardBoost - ComparedGuardedDamageNegation->GuardBoost);
	}
	else
	{		
		GuardedDamageNegation_PhysicalRow->SetValueColor(NormalColor);
		GuardedDamageNegation_MagicRow->SetValueColor(NormalColor);
		GuardedDamageNegation_FireRow->SetValueColor(NormalColor);
		GuardedDamageNegation_LightningRow->SetValueColor(NormalColor);
		GuardedDamageNegation_HolyRow->SetValueColor(NormalColor);
		GuardedDamageNegation_GuardBoostRow->SetValueColor(NormalColor);
	}				
}

void UItemPropertiesWidget::ShowAttributeScaling(const FAttributeScaling* AttributeScalingInfo, const FAttributeScaling* ComparedAttributeScaling)
{
	AttributeScaling->SetVisibility(ESlateVisibility::Visible);
	
	AttributeScaling_Str_Row->SetEnumValue(StaticEnum<EScalingValue>(), static_cast<uint8>(AttributeScalingInfo->Str));
	AttributeScaling_Dex_Row->SetEnumValue(StaticEnum<EScalingValue>(), static_cast<uint8>(AttributeScalingInfo->Dex));
	AttributeScaling_Int_Row->SetEnumValue(StaticEnum<EScalingValue>(), static_cast<uint8>(AttributeScalingInfo->Int));
	AttributeScaling_Fai_Row->SetEnumValue(StaticEnum<EScalingValue>(), static_cast<uint8>(AttributeScalingInfo->Fai));
	AttributeScaling_Arc_Row->SetEnumValue(StaticEnum<EScalingValue>(), static_cast<uint8>(AttributeScalingInfo->Arc));
	
	if (ComparedAttributeScaling)
	{
		SetRowValueColor(AttributeScaling_Str_Row, static_cast<int32>(AttributeScalingInfo->Str) - static_cast<int32>(ComparedAttributeScaling->Str));
		SetRowValueColor(AttributeScaling_Dex_Row, static_cast<int32>(AttributeScalingInfo->Dex) - static_cast<int32>(ComparedAttributeScaling->Dex));
		SetRowValueColor(AttributeScaling_Int_Row, static_cast<int32>(AttributeScalingInfo->Int) - static_cast<int32>(ComparedAttributeScaling->Int));
		SetRowValueColor(AttributeScaling_Fai_Row, static_cast<int32>(AttributeScalingInfo->Fai) - static_cast<int32>(ComparedAttributeScaling->Fai));
		SetRowValueColor(AttributeScaling_Arc_Row, static_cast<int32>(AttributeScalingInfo->Arc) - static_cast<int32>(ComparedAttributeScaling->Arc));
	}
	else
	{		
		AttributeScaling_Str_Row->SetValueColor(NormalColor);
		AttributeScaling_Dex_Row->SetValueColor(NormalColor);
		AttributeScaling_Int_Row->SetValueColor(NormalColor);
		AttributeScaling_Fai_Row->SetValueColor(NormalColor);
		AttributeScaling_Arc_Row->SetValueColor(NormalColor);
	}	
}

void UItemPropertiesWidget::ShowAttributeRequired(const FAttributeRequired* AttributeRequiredInfo, const FAttributeRequired* ComparedAttributeRequired)
{
	AttributeScaling->SetVisibility(ESlateVisibility::Visible);
	
	AttributeRequired_Str_Row->SetIntValue(AttributeRequiredInfo->Str);
	AttributeRequired_Dex_Row->SetIntValue(AttributeRequiredInfo->Dex);
	AttributeRequired_Int_Row->SetIntValue(AttributeRequiredInfo->Int);
	AttributeRequired_Fai_Row->SetIntValue(AttributeRequiredInfo->Fai);
	AttributeRequired_Arc_Row->SetIntValue(AttributeRequiredInfo->Arc);

	if (ComparedAttributeRequired)
	{
		SetRowValueColor(AttributeRequired_Str_Row, ComparedAttributeRequired->Str - AttributeRequiredInfo->Str);
		SetRowValueColor(AttributeRequired_Dex_Row, ComparedAttributeRequired->Dex - AttributeRequiredInfo->Dex);
		SetRowValueColor(AttributeRequired_Int_Row, ComparedAttributeRequired->Int - AttributeRequiredInfo->Int);
		SetRowValueColor(AttributeRequired_Fai_Row, ComparedAttributeRequired->Fai - AttributeRequiredInfo->Fai);
		SetRowValueColor(AttributeRequired_Arc_Row, ComparedAttributeRequired->Arc - AttributeRequiredInfo->Arc);
	}
	else
	{		
		AttributeRequired_Str_Row->SetValueColor(NormalColor);
		AttributeRequired_Dex_Row->SetValueColor(NormalColor);
		AttributeRequired_Int_Row->SetValueColor(NormalColor);
		AttributeRequired_Fai_Row->SetValueColor(NormalColor);
		AttributeRequired_Arc_Row->SetValueColor(NormalColor);
	}
}

void UItemPropertiesWidget::ShowDamageNegation(const FDamageNegation* DamageNegationInfo, const FDamageNegation* ComparedDamageNegation)
{
	DamageNegation->SetVisibility(ESlateVisibility::Visible);

	DamageNegation_PhysicalRow->SetFloatValue(DamageNegationInfo->Physical);
	DamageNegation_VSStrikeRow->SetFloatValue(DamageNegationInfo->Strike);
	DamageNegation_VSSlashRow->SetFloatValue(DamageNegationInfo->Slash);
	DamageNegation_VSPierceRow->SetFloatValue(DamageNegationInfo->Pierce);
	DamageNegation_MagicRow->SetFloatValue(DamageNegationInfo->Magic);
	DamageNegation_FireRow->SetFloatValue(DamageNegationInfo->Fire);
	DamageNegation_LightningRow->SetFloatValue(DamageNegationInfo->Lightning);
	DamageNegation_HolyRow->SetFloatValue(DamageNegationInfo->Holy);

	if (ComparedDamageNegation)
	{
		SetRowValueColor(DamageNegation_PhysicalRow, DamageNegationInfo->Physical - ComparedDamageNegation->Physical);
		SetRowValueColor(DamageNegation_VSStrikeRow, DamageNegationInfo->Strike - ComparedDamageNegation->Strike);
		SetRowValueColor(DamageNegation_VSSlashRow, DamageNegationInfo->Slash - ComparedDamageNegation->Slash);
		SetRowValueColor(DamageNegation_VSPierceRow, DamageNegationInfo->Pierce - ComparedDamageNegation->Pierce);
		SetRowValueColor(DamageNegation_MagicRow, DamageNegationInfo->Magic - ComparedDamageNegation->Magic);
		SetRowValueColor(DamageNegation_FireRow, DamageNegationInfo->Fire - ComparedDamageNegation->Fire);
		SetRowValueColor(DamageNegation_LightningRow, DamageNegationInfo->Lightning - ComparedDamageNegation->Lightning);
		SetRowValueColor(DamageNegation_HolyRow, DamageNegationInfo->Holy - ComparedDamageNegation->Holy);
	}
	else
	{		
		DamageNegation_PhysicalRow->SetValueColor(NormalColor);
		DamageNegation_VSStrikeRow->SetValueColor(NormalColor);
		DamageNegation_VSSlashRow->SetValueColor(NormalColor);
		DamageNegation_VSPierceRow->SetValueColor(NormalColor);
		DamageNegation_MagicRow->SetValueColor(NormalColor);
		DamageNegation_FireRow->SetValueColor(NormalColor);
		DamageNegation_LightningRow->SetValueColor(NormalColor);
		DamageNegation_HolyRow->SetValueColor(NormalColor);
	}
}

void UItemPropertiesWidget::ShowResistance(const FResistance* ResistanceInfo, const FResistance* ComparedResistance)
{
	Resistance->SetVisibility(ESlateVisibility::Visible);

	Resistance_ImmunityRow->SetIntValue(ResistanceInfo->Immunity);
	Resistance_RobustnessRow->SetIntValue(ResistanceInfo->Robustness);
	Resistance_FocusRow->SetIntValue(ResistanceInfo->Focus);
	Resistance_DeathRow->SetIntValue(ResistanceInfo->Death);

	if (ComparedResistance)
	{
		SetRowValueColor(Resistance_ImmunityRow, ResistanceInfo->Immunity - ComparedResistance->Immunity);
		SetRowValueColor(Resistance_RobustnessRow, ResistanceInfo->Robustness - ComparedResistance->Robustness);
		SetRowValueColor(Resistance_FocusRow, ResistanceInfo->Focus - ComparedResistance->Focus);
		SetRowValueColor(Resistance_DeathRow, ResistanceInfo->Death - ComparedResistance->Death);
	}
	else
	{		
		Resistance_ImmunityRow->SetValueColor(NormalColor);
		Resistance_RobustnessRow->SetValueColor(NormalColor);
		Resistance_FocusRow->SetValueColor(NormalColor);
		Resistance_DeathRow->SetValueColor(NormalColor);
	}
}

void UItemPropertiesWidget::SetRowValueColor(UPropertyRowWidget* RowWidget, float Value)
{
	if (Value > 0.f)
	{
		RowWidget->SetValueColor(PositiveColor);
	} else if (Value < 0.f)
	{
		RowWidget->SetValueColor(NegativeColor);
	}
	else
	{
		RowWidget->SetValueColor(NormalColor);
	}
}
