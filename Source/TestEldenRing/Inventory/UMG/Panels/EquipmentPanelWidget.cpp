// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentPanelWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

#include "TestEldenRing/Inventory/UMG/Slots/ItemEquipmentSlotWidget.h"

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

	for (int32 L_Row = 0; L_Row < EquipmentSlotsVBox->GetChildrenCount(); L_Row++)
	{
		UHorizontalBox* L_ChildHBox = Cast<UHorizontalBox>(EquipmentSlotsVBox->GetChildAt(L_Row));
		for (auto L_SlotWidget : L_ChildHBox->GetAllChildren())
		{
			UItemEquipmentSlotWidget* L_SlotItemWidget = Cast<UItemEquipmentSlotWidget>(L_SlotWidget);
			L_SlotItemWidget->OnSlotSelected.BindUObject(this, &UEquipmentPanelWidget::SetSelectedEquipSlot);
			L_SlotItemWidget->OnSlotClicked.BindUObject(this, &UEquipmentPanelWidget::SetItemEquipped);
		}
	}

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
		
		ChangedLookItemInfo();		
	}
}

FText UEquipmentPanelWidget::GetSelectedSlotName() const
{
	return CurrentSelectedSlotWidget->GetSlotName();
}

EEquipmentSlot UEquipmentPanelWidget::GetSelectedSlotType() const
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

void UEquipmentPanelWidget::SetSelectedEquipSlot(UBaseSlotWidget* SlotWidget)
{
	if (CurrentSelectedSlotWidget)
	{
		CurrentSelectedSlotWidget->ChangeSelectionState(false);
	}
	
	SlotWidget->ChangeSelectionState(true);
	CurrentSelectedSlotWidget = Cast<UItemEquipmentSlotWidget>(SlotWidget);
	
	ItemNameText->SetText(CurrentSelectedSlotWidget->GetItemName());
	SlotTypeText->SetText(CurrentSelectedSlotWidget->GetSlotName());

	ChangedLookItemInfo();
	
}

void UEquipmentPanelWidget::ChangedLookItemInfo() const
{
	if (OnChangedLookItemInfo.IsBound())
	{
		if (CurrentSelectedSlotWidget->GetInventoryItemSlot())
		{
			OnChangedLookItemInfo.Execute(
				CurrentSelectedSlotWidget->GetInventoryItemSlot()->GetItemInfo(), CurrentSelectedSlotWidget->GetInventoryItemSlot(), nullptr);
		}
		else
		{
			OnChangedLookItemInfo.Execute(
				InventoryAC->GetEmptyEquipmentInfo(CurrentSelectedSlotWidget->EquipmentSlotType), CurrentSelectedSlotWidget->GetInventoryItemSlot(), nullptr);
		}
	}
}

void UEquipmentPanelWidget::SetItemEquipped(UBaseSlotWidget* SlotWidget) const
{
	if (OnEquipSelectionStart.IsBound())
	{
		OnEquipSelectionStart.Execute();
	}
}
