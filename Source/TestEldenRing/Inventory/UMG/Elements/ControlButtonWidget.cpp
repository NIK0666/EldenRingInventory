// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlButtonWidget.h"

#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

bool UControlButtonWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (Button1Brush.DrawAs == ESlateBrushDrawType::NoDrawType)
	{
		SizeBox1->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		SizeBox1->SetVisibility(ESlateVisibility::Visible);
		Button1Image->SetBrush(Button1Brush);
	}

	if (Button2Brush.DrawAs == ESlateBrushDrawType::NoDrawType)
	{
		SizeBox2->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		SizeBox2->SetVisibility(ESlateVisibility::Visible);
		Button2Image->SetBrush(Button2Brush);
	}
	
	SetDescription(Description);
	

	return true;
}

void UControlButtonWidget::SetDescription(const FText& NewDescription)
{
	Description = NewDescription;
	DescriptionText->SetText(FText::FromString(": " + NewDescription.ToString()));
}
