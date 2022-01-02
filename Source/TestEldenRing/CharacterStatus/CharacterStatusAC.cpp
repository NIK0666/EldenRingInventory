// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatusAC.h"

#include "TestEldenRing/Core/ERPlayerController.h"


UCharacterStatusAC::UCharacterStatusAC()
{	
}

FCharacterStatus* UCharacterStatusAC::GetStatus()
{
	return &BaseStatus;
}

UInventoryAC* UCharacterStatusAC::GetInventoryAC()
{
	if (IsValid(InventoryAC))
	{
		return InventoryAC;
	}
	
	const AERPlayerController* PlayerController = Cast<AERPlayerController>(GetWorld()->GetFirstPlayerController());
	if (IsValid(PlayerController))
	{
		InventoryAC = PlayerController->GetInventoryAC();
		return InventoryAC;
	}

	return nullptr;
}

float UCharacterStatusAC::GetCurrentWeight()
{
	auto Equipments = GetInventoryAC()->GetEquipments();

	float OutWeight = 0.f;
	
	for (auto Equipment : Equipments)
	{
		const UInventoryItemSlot* L_InventoryItemSlot = Equipment.Value.InventoryItemSlot;
		
		if (!IsValid(L_InventoryItemSlot))
		{
			continue;
		}

		switch (L_InventoryItemSlot->EquipmentSlotType)
		{
		case EEquipmentSlot::LHand1: 
		case EEquipmentSlot::LHand2: 
		case EEquipmentSlot::LHand3: 
		case EEquipmentSlot::RHand1: 
		case EEquipmentSlot::RHand2: 
		case EEquipmentSlot::RHand3:
		case EEquipmentSlot::Helm: 
		case EEquipmentSlot::Armor: 
		case EEquipmentSlot::Gloves: 
		case EEquipmentSlot::Boots:
		case EEquipmentSlot::Amulet1: 
		case EEquipmentSlot::Amulet2:
			OutWeight += Equipment.Value.InventoryItemSlot->GetItemInfo()->Weight;
			break;
		default: break;
		}		
	}
	return OutWeight;
}

