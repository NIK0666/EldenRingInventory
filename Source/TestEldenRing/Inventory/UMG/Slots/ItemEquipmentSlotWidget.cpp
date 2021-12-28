// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEquipmentSlotWidget.h"

#include "Components/Image.h"

bool UItemEquipmentSlotWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	if (!IsValid(PlaceholderImage))
	{
		return false;
	}
	PlaceholderImage->SetBrush(PlaceholderBrush);

	return true;	
}


void UItemEquipmentSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	SetSelected();
}

FText UItemEquipmentSlotWidget::GetSlotName()
{
	return SlotName;
}
