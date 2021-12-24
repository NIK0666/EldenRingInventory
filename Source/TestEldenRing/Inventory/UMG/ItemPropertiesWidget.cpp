// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPropertiesWidget.h"

#include "TestEldenRing/Inventory/InventoryItemSlot.h"

void UItemPropertiesWidget::Update(EEquipmentSlot EquipmentSlotType, const UInventoryItemSlot* InventoryItemSlot)
{
	switch (EquipmentSlotType)
	{
	case EEquipmentSlot::None: break;
	case EEquipmentSlot::LHand1:
	case EEquipmentSlot::LHand2:
	case EEquipmentSlot::LHand3:
	case EEquipmentSlot::RHand1:
	case EEquipmentSlot::RHand2:
	case EEquipmentSlot::RHand3:
		{
			if (InventoryItemSlot == nullptr)
			{
			}
			else
			{
				const FWeaponItem* WeaponItem = InventoryItemSlot->ItemRow.DataTable->FindRow<FWeaponItem>(
					InventoryItemSlot->ItemRow.RowName, "FWeaponItem");

				if (WeaponItem)
				{
					UE_LOG(LogTemp, Error, TEXT("%s"), *WeaponItem->ItemName.ToString());
					UE_LOG(LogTemp, Warning, TEXT("Weapon Type: %s"),
					       *StaticEnum<EWeaponSubtype>()->GetDisplayNameTextByValue(static_cast<int64>(WeaponItem->
						       WeaponSubtype)).ToString());
					UE_LOG(LogTemp, Warning, TEXT("Damage Type: %s"),
					       *StaticEnum<EDamageType>()->GetDisplayNameTextByValue(static_cast<int64>(WeaponItem->
						       DamageType)).ToString());
					UE_LOG(LogTemp, Log, TEXT(""));
					UE_LOG(LogTemp, Warning, TEXT("Super Attack: %s"),
					       *WeaponItem->SuperAttack.AttackName.ToString());
					UE_LOG(LogTemp, Warning, TEXT("FP Cost: %d"), WeaponItem->SuperAttack.FPCost);
					UE_LOG(LogTemp, Warning, TEXT("Weight: %f"), WeaponItem->Weight);
					UE_LOG(LogTemp, Log, TEXT("--------------------------------------"));
				}
				break;
			}
		}

	case EEquipmentSlot::Arrows1: break;
	case EEquipmentSlot::Arrows2: break;
	case EEquipmentSlot::Bolts1: break;
	case EEquipmentSlot::Bolts2: break;
	case EEquipmentSlot::Helm: break;
	case EEquipmentSlot::Armor: break;
	case EEquipmentSlot::Gloves: break;
	case EEquipmentSlot::Boots: break;
	case EEquipmentSlot::Amulet1: break;
	case EEquipmentSlot::Amulet2: break;
	case EEquipmentSlot::Consumables1: break;
	case EEquipmentSlot::Consumables2: break;
	case EEquipmentSlot::Consumables3: break;
	case EEquipmentSlot::Consumables4: break;
	case EEquipmentSlot::Consumables5: break;
	case EEquipmentSlot::Consumables6: break;
	case EEquipmentSlot::Consumables7: break;
	case EEquipmentSlot::Consumables8: break;
	case EEquipmentSlot::Consumables9: break;
	case EEquipmentSlot::Consumables10: break;
	default: ;
	}
}
