// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPropertiesWidget.h"

#include "PropertyRowWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "TestEldenRing/Inventory/InventoryItemSlot.h"

void UItemPropertiesWidget::Update(FItem* ItemInfo)
{

	IconBlock_IconImage->SetVisibility(ESlateVisibility::Collapsed);
	
	Common->SetVisibility(ESlateVisibility::Visible);
	DamageNegation->SetVisibility(ESlateVisibility::Visible);
	AttackPower->SetVisibility(ESlateVisibility::Visible);

	Common_NameText->SetText(ItemInfo->ItemName);
	Common_WeightRow->SetFloatValue(ItemInfo->Weight);
	
	// if (IsEmptySlot)
	// {
	// 	Common_NameText->SetText(FText::FromString("Fists"));
	// 	Common_ItemTypeRow->SetTextValue(FText::FromString("Fists"));
	// 	Common_DamageTypeRow->SetTextValue(StaticEnum<EDamageType>()->GetDisplayNameTextByValue(static_cast<int64>(EDamageType::Strike)));
	// 	Common_SuperAttackNameRow->SetStringValue("-");
	// 	Common_FPCostRow->SetFloatValue(0.f);
	// 	Common_WeightRow->SetFloatValue(0.f);
	// 	
	// 	AttackPower_PhysicalRow->SetIntValue(20);
	// 	AttackPower_MagicRow->SetIntValue(0);
	// 	AttackPower_FireRow->SetIntValue(0);
	// 	AttackPower_LightningRow->SetIntValue(0);
	// 	AttackPower_HolyRow->SetIntValue(0);
	// 	AttackPower_CriticalRow->SetIntValue(100);
	// }
	// else
	// {
	//
	// if (const FWeaponItem* WeaponItem = InventoryItemSlot->ItemRow.DataTable->FindRow<FWeaponItem>(
	// 	InventoryItemSlot->ItemRow.RowName, "FWeaponItem"))
	// {
	// 	Common_NameText->SetText(WeaponItem->ItemName);
	// 	Common_ItemTypeRow->SetTextValue(StaticEnum<EWeaponSubtype>()->GetDisplayNameTextByValue(static_cast<int64>(WeaponItem->WeaponSubtype)));
	// 	Common_DamageTypeRow->SetTextValue(StaticEnum<EDamageType>()->GetDisplayNameTextByValue(static_cast<int64>(WeaponItem->DamageType)));
	// 	Common_SuperAttackNameRow->SetTextValue(WeaponItem->SuperAttack.AttackName);
	// 	Common_FPCostRow->SetFloatValue(WeaponItem->SuperAttack.FPCost);
	// 	Common_WeightRow->SetFloatValue(WeaponItem->Weight);
	//
	// 	IconBlock_IconImage->SetBrushFromTexture(WeaponItem->Icon);
	// 	IconBlock_IconImage->SetVisibility(ESlateVisibility::Visible);
	//
	// 	AttackPower_PhysicalRow->SetIntValue(WeaponItem->AttackPower.Physical);
	// 	AttackPower_MagicRow->SetIntValue(WeaponItem->AttackPower.Magic);
	// 	AttackPower_FireRow->SetIntValue(WeaponItem->AttackPower.Fire);
	// 	AttackPower_LightningRow->SetIntValue(WeaponItem->AttackPower.Lightning);
	// 	AttackPower_HolyRow->SetIntValue(WeaponItem->AttackPower.Holy);
	// 	AttackPower_CriticalRow->SetIntValue(WeaponItem->AttackPower.Critical);
	// 	
	// 	//DamageNegation_PhysicalRow->SetIntValue(WeaponItem->GuardedDamageNegation.Physical)
	// 	
	// }
	
}
