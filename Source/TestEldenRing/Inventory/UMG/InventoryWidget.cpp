// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "ItemEquipmentSlotWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/InputSettings.h"
#include "TestEldenRing/Core/ERPlayerController.h"
#include "TestEldenRing/Inventory/InventoryAC.h"

bool UInventoryWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	return true;
}

FReply UInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (CheckIsPressedActionKey(FName("UI_Left"), InKeyEvent.GetKey()))
	{
		MoveHorizontalSelection(false);
	}
	else if (CheckIsPressedActionKey(FName("UI_Right"), InKeyEvent.GetKey()))
	{
		MoveHorizontalSelection(true);
	}
	else if (CheckIsPressedActionKey(FName("UI_Up"), InKeyEvent.GetKey()))
	{
		MoveVerticalSelection(false);
	}
	else if (CheckIsPressedActionKey(FName("UI_Down"), InKeyEvent.GetKey()))
	{
		MoveVerticalSelection(true);
	}
	else if (CheckIsPressedActionKey(FName("UI_EquipRemove"), InKeyEvent.GetKey()))
	{
		UE_LOG(LogTemp, Log, TEXT("UI_REMOVE: %s"), *InKeyEvent.GetKey().ToString());
		EquipRemove();
	}	
	
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AERPlayerController* PlayerController = Cast<AERPlayerController>(GetOwningPlayer());
	if (IsValid(PlayerController))
	{
		InventoryAC = PlayerController->GetInventoryAC();
		InventoryAC->EquipItemChanged.AddWeakLambda(
			this, [this](EEquipmentSlot EquipmentSlot, UInventoryItemSlot* FromInventoryItemSlot,
			             UInventoryItemSlot* ToInventoryItemSlot)
			{
				UItemEquipmentSlotWidget* ItemEquipmentSlotWidget = GetItemEquipmentSlotWidget(EquipmentSlot);
				ItemEquipmentSlotWidget->Update(ToInventoryItemSlot);

				if (CurrentSelectedSlotWidget == ItemEquipmentSlotWidget)
				{
					ItemNameText->SetText(ItemEquipmentSlotWidget->GetItemName());
				}
			});
	}
	
	EquipSlotLHand1->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotLHand2->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotLHand3->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotRHand1->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotRHand2->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotRHand3->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotArrows1->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotArrows2->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotBolts1->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotBolts2->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotHelm->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotArmor->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotGloves->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotBoots->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotAmulet1->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotAmulet2->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotConsumables1->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotConsumables2->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotConsumables3->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotConsumables4->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotConsumables5->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotConsumables6->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotConsumables7->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotConsumables8->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotConsumables9->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);
	EquipSlotConsumables10->SlotSelected.BindUObject(this, &UInventoryWidget::SetSelectedEquipSlot);

	SetSelectedEquipSlot(EquipSlotRHand1);
	
}

UItemEquipmentSlotWidget* UInventoryWidget::GetItemEquipmentSlotWidget(EEquipmentSlot EquipmentSlotType) const
{
	switch (EquipmentSlotType)
		{
		case EEquipmentSlot::LHand1:
			return EquipSlotLHand1;
		case EEquipmentSlot::LHand2:
			return EquipSlotLHand2;
		case EEquipmentSlot::LHand3: 
			return EquipSlotLHand3;
		case EEquipmentSlot::RHand1: 
			return EquipSlotRHand1;
		case EEquipmentSlot::RHand2: 
			return EquipSlotRHand2;
		case EEquipmentSlot::RHand3: 
			return EquipSlotRHand3;
		case EEquipmentSlot::Arrows1: 
			return EquipSlotArrows1;
		case EEquipmentSlot::Arrows2: 
			return EquipSlotArrows2;
		case EEquipmentSlot::Bolts1: 
			return EquipSlotBolts1;
		case EEquipmentSlot::Bolts2: 
			return EquipSlotBolts2;
		case EEquipmentSlot::Helm: 
			return EquipSlotHelm;
		case EEquipmentSlot::Armor: 
			return EquipSlotArmor;
		case EEquipmentSlot::Gloves: 
			return EquipSlotGloves;
		case EEquipmentSlot::Boots: 
			return EquipSlotBoots;
		case EEquipmentSlot::Amulet1: 
			return EquipSlotAmulet1;
		case EEquipmentSlot::Amulet2: 
			return EquipSlotAmulet2;
		case EEquipmentSlot::Consumables1: 
			return EquipSlotConsumables1;
		case EEquipmentSlot::Consumables2: 
			return EquipSlotConsumables2;
		case EEquipmentSlot::Consumables3: 
			return EquipSlotConsumables3;
		case EEquipmentSlot::Consumables4: 
			return EquipSlotConsumables4;
		case EEquipmentSlot::Consumables5: 
			return EquipSlotConsumables5;
		case EEquipmentSlot::Consumables6: 
			return EquipSlotConsumables6;
		case EEquipmentSlot::Consumables7: 
			return EquipSlotConsumables7;
		case EEquipmentSlot::Consumables8: 
			return EquipSlotConsumables8;
		case EEquipmentSlot::Consumables9: 
			return EquipSlotConsumables9;
		case EEquipmentSlot::Consumables10: 
			return EquipSlotConsumables10;
		default:
			UE_LOG(LogTemp, Error, TEXT("MISSING Equipment slot category"))
			return nullptr;
		}
}

void UInventoryWidget::SetSelectedEquipSlot(UItemEquipmentSlotWidget* NewSelectedEquipSlot)
{
	if (CurrentSelectedSlotWidget)
	{
		CurrentSelectedSlotWidget->ChangeSelectionState(false);
	}	
	NewSelectedEquipSlot->ChangeSelectionState(true);
	CurrentSelectedSlotWidget = NewSelectedEquipSlot;
	
	ItemNameText->SetText(NewSelectedEquipSlot->GetItemName());
	SlotTypeText->SetText(NewSelectedEquipSlot->GetSlotName());
	
}

bool UInventoryWidget::CheckIsPressedActionKey(const FName& ActionName, const FKey& PressedKey)
{
	if (UInputSettings* InputSettings = UInputSettings::GetInputSettings())
	{
		TArray<FInputActionKeyMapping> OutMappings;
		InputSettings->GetActionMappingByName(ActionName, OutMappings);

		for (const FInputActionKeyMapping& OutMapping : OutMappings)			
		{
			if (OutMapping.Key == PressedKey)
			{
				return true;
			}
		}
	}
	return false;
}

void UInventoryWidget::MoveHorizontalSelection(bool bPositive) const
{
	if (CurrentSelectedSlotWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::MoveHorizontalSelection - SelectedSlot is Null!"));
		return;
	}
	
	int32 CurrentIndex = CurrentSelectedSlotWidget->GetParent()->GetChildIndex(CurrentSelectedSlotWidget);
	const int32 MaxIndex = CurrentSelectedSlotWidget->GetParent()->GetChildrenCount() - 1;


	CurrentIndex = (bPositive ? ((CurrentIndex < MaxIndex) ? CurrentIndex + 1 : 0) :
		((CurrentIndex > 0) ? CurrentIndex - 1 : MaxIndex));
	
	UItemEquipmentSlotWidget* NewSelected = Cast<UItemEquipmentSlotWidget>(CurrentSelectedSlotWidget->GetParent()->GetChildAt(CurrentIndex));
	NewSelected->SetSelected();
}

void UInventoryWidget::MoveVerticalSelection(bool bPositive) const
{
	if (CurrentSelectedSlotWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::MoveVerticalSelection - SelectedSlot is Null!"));
		return;
	}
	
	int32 CurrentSlotIndex = CurrentSelectedSlotWidget->GetParent()->GetChildIndex(CurrentSelectedSlotWidget);
	int32 CurrentBoxIndex = CurrentSelectedSlotWidget->GetParent()->GetParent()->GetChildIndex(CurrentSelectedSlotWidget->GetParent());	
	const int32 MaxBoxesIndex = CurrentSelectedSlotWidget->GetParent()->GetParent()->GetChildrenCount() - 1;
	
	if (bPositive)
	{		
		CurrentBoxIndex = CurrentBoxIndex == MaxBoxesIndex ? 0 : CurrentBoxIndex + 1;
	}
	else
	{
		CurrentBoxIndex = CurrentBoxIndex == 0 ? MaxBoxesIndex : CurrentBoxIndex - 1;		
	}
	
	const UHorizontalBox* CurrentBox = Cast<UHorizontalBox>(CurrentSelectedSlotWidget->GetParent()->GetParent()->GetChildAt(CurrentBoxIndex));		
	const int32 MaxSlotIndex = CurrentBox->GetChildrenCount() - 1;
	if (MaxSlotIndex < CurrentSlotIndex)
	{
		CurrentSlotIndex = MaxSlotIndex;
	}		
	UItemEquipmentSlotWidget* NewSelected = Cast<UItemEquipmentSlotWidget>(CurrentBox->GetChildAt(CurrentSlotIndex));
	NewSelected->SetSelected();	
}

void UInventoryWidget::EquipRemove() const
{
	if (!CurrentSelectedSlotWidget->IsEmptySlot())
	{
		InventoryAC->ClearEquipSlot(CurrentSelectedSlotWidget->EquipmentSlotType);
	}
}
