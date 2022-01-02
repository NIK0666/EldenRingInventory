// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPropertiesPanelWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "TestEldenRing/Inventory/InventoryItemSlot.h"

#include "TestEldenRing/Inventory/UMG/PropertyRowWidget.h"

void UItemPropertiesWidget::Update(FItem* ItemInfo, UInventoryItemSlot* InventoryItemSlot) const
{	
	Common->SetVisibility(ESlateVisibility::Visible);
	
	AttackPower->SetVisibility(ESlateVisibility::Collapsed);
	DamageNegation->SetVisibility(ESlateVisibility::Collapsed);
	GuardedDamageNegation->SetVisibility(ESlateVisibility::Collapsed);
	AttributeScaling->SetVisibility(ESlateVisibility::Collapsed);
	AttributeRequired->SetVisibility(ESlateVisibility::Collapsed);
	Resistance->SetVisibility(ESlateVisibility::Collapsed);
	Effects->SetVisibility(ESlateVisibility::Collapsed);
	
	Common_Row_0->Clear();
	Common_Row_1->Clear();
	Common_Row_2->Clear();
	Common_Row_3->Clear();
	Common_Row_4->Clear();
	Common_Row_5->Clear();

	Common_NameText->SetText(ItemInfo->ItemName);
	
	
	if (ItemInfo->Icon != nullptr)
	{
		IconBlock_IconImage->SetVisibility(ESlateVisibility::Visible);
		IconBlock_IconImage->SetBrushFromTexture(ItemInfo->Icon);
	}
	else
	{
		IconBlock_IconImage->SetVisibility(ESlateVisibility::Collapsed);
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
			
			Common_Row_0->SetEnumCaption(StaticEnum<EWeaponSubtype>(), static_cast<uint8>(WeaponItem->WeaponSubtype));			
			Common_Row_1->SetEnumCaption(StaticEnum<EDamageType>(), static_cast<uint8>(WeaponItem->DamageType));			
			Common_Row_3->SetCaption(WeaponItem->SuperAttack.AttackName);			
			Common_Row_4->SetCaption(FText::FromString("FP Cost"));
			Common_Row_4->SetFloatValue(WeaponItem->SuperAttack.FPCost);
			Common_Row_5->SetCaption(FText::FromString("Weight"));
			Common_Row_5->SetFloatValue(WeaponItem->Weight);

			ShowAttackPower(WeaponItem->AttackPower);
			ShowGuardedDamageNegation(WeaponItem->GuardedDamageNegation);
			ShowAttributeScaling(WeaponItem->AttributeScaling);
			ShowAttributeRequired(WeaponItem->AttributeRequired);
			ShowEffectsBlock(WeaponItem->PassiveEffects, FText::FromString("Passive Effects"));
			
		}		
		break;
	case EItemType::Armor:
		{
			DamageNegation->SetVisibility(ESlateVisibility::Visible);
			Resistance->SetVisibility(ESlateVisibility::Visible);

			FArmorItem* ArmorItem = static_cast<FArmorItem*>(ItemInfo);

			Common_Row_5->SetCaption(FText::FromString("Weight"));
			Common_Row_5->SetFloatValue(ArmorItem->Weight);

			ShowDamageNegation(ArmorItem->DamageNegation);
			ShowResistance(ArmorItem->Resistance);
		}
		break;
	case EItemType::Arrows:
		{
			AttackPower->SetVisibility(ESlateVisibility::Visible);
			Effects->SetVisibility(ESlateVisibility::Visible);			

			FArrowsItem* ArrowsItem = static_cast<FArrowsItem*>(ItemInfo);

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
			
			ShowAttackPower(ArrowsItem->AttackPower);
			ShowEffectsBlock(ArrowsItem->PassiveEffects, FText::FromString("Passive Effects"));
		}
		break;
	// case EItemType::Bolts:
	// 	break;
	case EItemType::Amulet:
		{
			Effects->SetVisibility(ESlateVisibility::Visible);

			FAmuletItem* AmuletItem = static_cast<FAmuletItem*>(ItemInfo);

			Common_Row_5->SetCaption(FText::FromString("Weight"));
			Common_Row_5->SetFloatValue(AmuletItem->Weight);

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

			ShowEffectsBlock(ConsumableItem->ItemEffects, FText::FromString("Item Effect"));
		}
		break;
	default: ;
	}
	
	
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

void UItemPropertiesWidget::ShowAttackPower(const FAttackPower& AttackPowerInfo) const
{
	AttackPower->SetVisibility(ESlateVisibility::Visible);
	
	AttackPower_PhysicalRow->SetIntValue(AttackPowerInfo.Physical);
	AttackPower_MagicRow->SetIntValue(AttackPowerInfo.Magic);
	AttackPower_FireRow->SetIntValue(AttackPowerInfo.Fire);
	AttackPower_LightningRow->SetIntValue(AttackPowerInfo.Lightning);
	AttackPower_HolyRow->SetIntValue(AttackPowerInfo.Holy);
}	

void UItemPropertiesWidget::ShowGuardedDamageNegation(const FGuardedDamageNegation& GuardedDamageNegationInfo) const
{
	GuardedDamageNegation->SetVisibility(ESlateVisibility::Visible);
	
	GuardedDamageNegation_PhysicalRow->SetFloatValue(GuardedDamageNegationInfo.Physical);
	GuardedDamageNegation_MagicRow->SetFloatValue(GuardedDamageNegationInfo.Magic);
	GuardedDamageNegation_FireRow->SetFloatValue(GuardedDamageNegationInfo.Fire);
	GuardedDamageNegation_LightningRow->SetFloatValue(GuardedDamageNegationInfo.Lightning);
	GuardedDamageNegation_HolyRow->SetFloatValue(GuardedDamageNegationInfo.Holy);
	GuardedDamageNegation_GuardBoostRow->SetIntValue(GuardedDamageNegationInfo.GuardBoost);
}

void UItemPropertiesWidget::ShowAttributeScaling(const FAttributeScaling& AttributeScalingInfo) const
{
	AttributeScaling->SetVisibility(ESlateVisibility::Visible);
	
	AttributeScaling_Str_Row->SetEnumValue(StaticEnum<EScalingValue>(), static_cast<uint8>(AttributeScalingInfo.Str));
	AttributeScaling_Dex_Row->SetEnumValue(StaticEnum<EScalingValue>(), static_cast<uint8>(AttributeScalingInfo.Dex));
	AttributeScaling_Int_Row->SetEnumValue(StaticEnum<EScalingValue>(), static_cast<uint8>(AttributeScalingInfo.Int));
	AttributeScaling_Fai_Row->SetEnumValue(StaticEnum<EScalingValue>(), static_cast<uint8>(AttributeScalingInfo.Fai));
	AttributeScaling_Arc_Row->SetEnumValue(StaticEnum<EScalingValue>(), static_cast<uint8>(AttributeScalingInfo.Arc));
}

void UItemPropertiesWidget::ShowAttributeRequired(const FAttributeRequired& AttributeRequiredInfo) const
{
	AttributeScaling->SetVisibility(ESlateVisibility::Visible);
	
	AttributeRequired_Str_Row->SetIntValue(AttributeRequiredInfo.Str);
	AttributeRequired_Dex_Row->SetIntValue(AttributeRequiredInfo.Dex);
	AttributeRequired_Int_Row->SetIntValue(AttributeRequiredInfo.Int);
	AttributeRequired_Fai_Row->SetIntValue(AttributeRequiredInfo.Fai);
	AttributeRequired_Arc_Row->SetIntValue(AttributeRequiredInfo.Arc);
}

void UItemPropertiesWidget::ShowDamageNegation(const FDamageNegation& DamageNegationInfo) const
{
	DamageNegation->SetVisibility(ESlateVisibility::Visible);

	DamageNegation_PhysicalRow->SetFloatValue(DamageNegationInfo.Physical);
	DamageNegation_VSStrikeRow->SetFloatValue(DamageNegationInfo.Strike);
	DamageNegation_VSSlashRow->SetFloatValue(DamageNegationInfo.Slash);
	DamageNegation_VSPierceRow->SetFloatValue(DamageNegationInfo.Pierce);
	DamageNegation_MagicRow->SetFloatValue(DamageNegationInfo.Magic);
	DamageNegation_FireRow->SetFloatValue(DamageNegationInfo.Fire);
	DamageNegation_LightningRow->SetFloatValue(DamageNegationInfo.Lightning);
	DamageNegation_HolyRow->SetFloatValue(DamageNegationInfo.Holy);
}

void UItemPropertiesWidget::ShowResistance(const FResistance& ResistanceInfo) const
{
	Resistance->SetVisibility(ESlateVisibility::Visible);

	Resistance_ImmunityRow->SetIntValue(ResistanceInfo.Immunity);
	Resistance_RobustnessRow->SetIntValue(ResistanceInfo.Robustness);
	Resistance_FocusRow->SetIntValue(ResistanceInfo.Focus);
	Resistance_DeathRow->SetIntValue(ResistanceInfo.Death);
}