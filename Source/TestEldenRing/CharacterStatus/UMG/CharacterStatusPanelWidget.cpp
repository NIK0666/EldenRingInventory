// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatusPanelWidget.h"

#include "Components/TextBlock.h"
#include "TestEldenRing/Core/ERPlayerController.h"
#include "TestEldenRing/Inventory/UMG/PropertyRowWidget.h"

bool UCharacterStatusPanelWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	return true;	
}

void UCharacterStatusPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AERPlayerController* PlayerController = Cast<AERPlayerController>(GetOwningPlayer());
	if (!IsValid(PlayerController))
	{		
		return;
	}

	CharacterStatusAC = PlayerController->GetCharacterStatusAC();
	UInventoryAC* InventoryAC = PlayerController->GetInventoryAC();

	InventoryAC->EquipItemChanged.AddWeakLambda(this, [this](
		EEquipmentSlot EquipmentSlot,	UInventoryItemSlot* FromInventoryItemSlot, UInventoryItemSlot* ToInventoryItemSlot)
	{
		Update();
	});

	Update();
	
}

void UCharacterStatusPanelWidget::Update() const
{
	const FCharacterStatus* CurrentStatus = CharacterStatusAC->GetStatus();

	LevelRow->SetIntValue(CurrentStatus->Level);
	RunesRow->SetIntValue(CurrentStatus->Runes);
	VigorRow->SetIntValue(CurrentStatus->Vigor);
	MindRow->SetIntValue(CurrentStatus->Mind);
	EnduranceRow->SetIntValue(CurrentStatus->Endurance);
	StrengthRow->SetIntValue(CurrentStatus->Strength);
	DexterityRow->SetIntValue(CurrentStatus->Dexterity);
	IntelligenceRow->SetIntValue(CurrentStatus->Intelligence);
	FaithRow->SetIntValue(CurrentStatus->Faith);
	ArcaneRow->SetIntValue(CurrentStatus->Arcane);	

	HPRow->SetIntPair(CharacterStatusAC->CurrentHP, CurrentStatus->HP);	
	FPRow->SetIntPair(CharacterStatusAC->CurrentFP,CurrentStatus->FP);	
	StaminaRow->SetIntValue(CurrentStatus->Stamina);	
	EquipLoadRow->SetFloatValue(CurrentStatus->EquipLoad);	
	EquipLoadRow->SetFloatPair(CharacterStatusAC->GetCurrentWeight(), CurrentStatus->EquipLoad);


	const float EquipLoadKoef = CharacterStatusAC->GetCurrentWeight() / CurrentStatus->EquipLoad;
	if (EquipLoadKoef < 0.33f)
	{
		EquipLoadText->SetText(StaticEnum<EEquipLoad>()->GetDisplayNameTextByValue(static_cast<uint8>(EEquipLoad::LightLoad)));
	}
	else if (EquipLoadKoef < 0.66f)
	{
		EquipLoadText->SetText(StaticEnum<EEquipLoad>()->GetDisplayNameTextByValue(static_cast<uint8>(EEquipLoad::MedLoad)));
	}
	else
	{
		EquipLoadText->SetText(StaticEnum<EEquipLoad>()->GetDisplayNameTextByValue(static_cast<uint8>(EEquipLoad::HeavyLoad)));
	}
	
	
	
	DiscoveryRow->SetFloatValue(CurrentStatus->Discovery);	
	MemorySlotsRow->SetIntValue(CurrentStatus->MemorySlotsCount);
}
