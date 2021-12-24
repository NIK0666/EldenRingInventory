// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentPanelWidget.h"

#include "ItemEquipmentSlotWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "TestEldenRing/Core/ERPlayerController.h"

bool UEquipmentPanelWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	return true;
}

void UEquipmentPanelWidget::NativeConstruct()
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
	
	EquipSlotLHand1->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotLHand2->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotLHand3->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotRHand1->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotRHand2->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotRHand3->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotArrows1->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotArrows2->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotBolts1->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotBolts2->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotHelm->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotArmor->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotGloves->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotBoots->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotAmulet1->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotAmulet2->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotConsumables1->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotConsumables2->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotConsumables3->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotConsumables4->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotConsumables5->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotConsumables6->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotConsumables7->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotConsumables8->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotConsumables9->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
	EquipSlotConsumables10->SlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);

	SetSelectedEquipSlot(EquipSlotRHand1);
}

void UEquipmentPanelWidget::MoveHorizontalSelection(bool bPositive) const
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

void UEquipmentPanelWidget::MoveVerticalSelection(bool bPositive) const
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

void UEquipmentPanelWidget::EquipRemove() const
{
	if (!CurrentSelectedSlotWidget->IsEmptySlot())
	{
		InventoryAC->ClearEquipSlot(CurrentSelectedSlotWidget->EquipmentSlotType);
	}
}

FText UEquipmentPanelWidget::GetSelectedSlotName()
{
	return CurrentSelectedSlotWidget->GetSlotName();
}

EEquipmentSlot UEquipmentPanelWidget::GetSelectedSlotType()
{
	return CurrentSelectedSlotWidget->EquipmentSlotType;
}

UItemEquipmentSlotWidget* UEquipmentPanelWidget::GetItemEquipmentSlotWidget(EEquipmentSlot EquipmentSlotType) const
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

void UEquipmentPanelWidget::SetSelectedEquipSlot(UItemEquipmentSlotWidget* NewSelectedEquipSlot)
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