// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPanelWidget.h"

#include "Components/TextBlock.h"
#include "Components/WrapBox.h"

#include "TestEldenRing/Inventory/UMG/Slots/ItemInventorySlotWidget.h"

void UInventoryPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();
	AERPlayerController* PlayerController = Cast<AERPlayerController>(GetOwningPlayer());
	if (IsValid(PlayerController))
	{
		InventoryAC = PlayerController->GetInventoryAC();
	}

	for (const auto L_ItemWidget : InventoryWrapBox->GetAllChildren())
	{
		UItemInventorySlotWidget* L_SlotWidget = Cast<UItemInventorySlotWidget>(L_ItemWidget);
		L_SlotWidget->OnSlotSelected.BindUObject(this, &UInventoryPanelWidget::SetSelectedInventorySlot);

		L_SlotWidget->OnSlotClicked.BindWeakLambda(this, [this](UBaseSlotWidget* SlotWidget)
		{
			if (OnEquipSelection.IsBound())
			{				
				OnEquipSelection.Execute();
			}
		});
	}
}

void UInventoryPanelWidget::Update(const FText& SlotNameText, EEquipmentSlot EquipmentSlot)
{
	InventorySlotTypeText->SetText(SlotNameText);

	const FEquipmentSlot* ItemSlot = InventoryAC->GetInventoryItemSlotByEquipmentType(EquipmentSlot);
	
	if (ItemSlot != nullptr)
	{
		Items = InventoryAC->GetInventoryItems(ItemSlot->DataTable);
	}
	else
	{
		Items.Empty();
	}
	
	SelectedEquipmentSlot = EquipmentSlot;
	
	for (int32 i = 0; i < InventoryWrapBox->GetChildrenCount(); i++)
	{
		UItemInventorySlotWidget* ItemWidget = Cast<UItemInventorySlotWidget>(InventoryWrapBox->GetChildAt(i));

		if (i < Items.Num())
		{
			ItemWidget->Update(Items[i]);
		}
		else
		{
			ItemWidget->Update(nullptr);
		}		
	}

	if (Items.Num() > 0)
	{
		//TODO Ищем выбранный слот и его выделяем.
		Cast<UItemInventorySlotWidget>(InventoryWrapBox->GetChildAt(0))->SetSelected();
	}
	
}

void UInventoryPanelWidget::SetSelectedInventorySlot(UBaseSlotWidget* NewSlotWidget)
{
	if (CurrentSelectedInventorySlotWidget)
	{
		CurrentSelectedInventorySlotWidget->ChangeSelectionState(false);
	}	
	NewSlotWidget->ChangeSelectionState(true);
	CurrentSelectedInventorySlotWidget = NewSlotWidget;

	UInventoryItemSlot* ItemSlot = NewSlotWidget->GetInventoryItemSlot();
	if (ItemSlot)
	{
		ItemNameText->SetText(ItemSlot->GetItemInfo()->ItemName);
	}
	else
	{
		ItemNameText->SetText(FText::FromString("-"));
	}
	
	//TODO Fix Here
	// if (OnChangedCurrentItemSlot.IsBound())
	// {
	// 	OnChangedCurrentItemSlot.Execute(NewSelectedInventorySlot->GetInventoryItemSlot());
	// }
}

void UInventoryPanelWidget::EquipSelectedItem() const
{	
	InventoryAC->SetEquipItemToSlot(CurrentSelectedInventorySlotWidget->GetInventoryItemSlot(), SelectedEquipmentSlot);
}

UBaseSlotWidget* UInventoryPanelWidget::GetSelectedSlotWidget() const
{
	return CurrentSelectedInventorySlotWidget;
}

void UInventoryPanelWidget::MoveHorizontalSelection(bool bPositive) const
{
	if (CurrentSelectedInventorySlotWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryPanelWidget::MoveHorizontalSelection - SelectedSlot is NULL!"));
		return;
	}

	int32 CurrentSlotIndex = InventoryWrapBox->GetChildIndex(CurrentSelectedInventorySlotWidget);
	const int32 MaxSlotIndex = Items.Num() - 1;

	if (MaxSlotIndex <= 0 && CurrentSlotIndex == 0)
	{
		return;
	}

	if (bPositive)
	{
		CurrentSlotIndex = (CurrentSlotIndex + 1 > MaxSlotIndex) ? 0 : CurrentSlotIndex + 1;
	}
	else
	{
		CurrentSlotIndex = (CurrentSlotIndex  < 1) ? MaxSlotIndex : CurrentSlotIndex - 1;
	}

	UItemInventorySlotWidget* NewSelected = Cast<UItemInventorySlotWidget>(InventoryWrapBox->GetChildAt(CurrentSlotIndex));
	NewSelected->SetSelected();

}

void UInventoryPanelWidget::MoveVerticalSelection(bool bPositive)
{
	if (CurrentSelectedInventorySlotWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryPanelWidget::MoveHorizontalSelection - SelectedSlot is NULL!"));
		return;
	}

	int32 CurrentSlotIndex = InventoryWrapBox->GetChildIndex(CurrentSelectedInventorySlotWidget);
	const int32 MaxSlotIndex = Items.Num() - 1;

	if (MaxSlotIndex <= 0 && CurrentSlotIndex == 0)
	{
		return;
	}

	if (bPositive)
	{
		CurrentSlotIndex = (CurrentSlotIndex + 5 > MaxSlotIndex) ? CurrentSlotIndex % 5 : CurrentSlotIndex + 5;
	}
	else
	{
		if (CurrentSlotIndex < 5)
		{
			const int32 Rows = (MaxSlotIndex / 5);
			CurrentSlotIndex = (Rows * 5) + CurrentSlotIndex;
			if (CurrentSlotIndex > MaxSlotIndex)
			{
				CurrentSlotIndex -= 5;
			}			
		}
		else
		{
			CurrentSlotIndex -= 5;
		}
		
	}

	UItemInventorySlotWidget* NewSelected = Cast<UItemInventorySlotWidget>(InventoryWrapBox->GetChildAt(CurrentSlotIndex));
	NewSelected->SetSelected();	
}

void UInventoryPanelWidget::EndHidePanel()
{
	if (IsValid(CurrentSelectedInventorySlotWidget))
	{
		CurrentSelectedInventorySlotWidget->ChangeSelectionState(false);
		CurrentSelectedInventorySlotWidget = nullptr;
	}
}
