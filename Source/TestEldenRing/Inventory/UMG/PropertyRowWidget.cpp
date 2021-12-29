// Fill out your copyright notice in the Description page of Project Settings.


#include "PropertyRowWidget.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

bool UPropertyRowWidget::Initialize()
{	
	if (!Super::Initialize())
	{
		return false;
	}
	
	if (!IsValid(CaptionText))
	{
		return false;
	}
	
	if (!IsValid(ValueText))
	{
		return false;
	}
	
	if (!IsValid(RootSizeBox))
	{
		return false;
	}

	ValueText->SetVisibility(bIsValueVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	
	ValueText->SetText(Value);
	
	CaptionText->SetText(Caption);

	RootSizeBox->SetWidthOverride(WidthMax);	
	
	return true;
}

void UPropertyRowWidget::SetTextValue(const FText& NewValue)
{
	ValueText->SetVisibility(ESlateVisibility::Visible);
	ValueText->SetText(NewValue);
}

void UPropertyRowWidget::SetStringValue(const FString& NewValue)
{
	SetTextValue(FText::FromString(NewValue));
}

void UPropertyRowWidget::SetIntValue(const int32& NewValue)
{
	SetStringValue(FString::FromInt(NewValue));
}

void UPropertyRowWidget::SetFloatValue(const float& NewValue)
{
	const int32 Decimal = FMath::TruncToInt(NewValue);
	const int32 Tenth = FMath::RoundToInt(NewValue * 10) - Decimal * 10;
	SetStringValue(FString::FromInt(Decimal) + "." + FString::FromInt(Tenth));
}

void UPropertyRowWidget::SetCaption(const FText& NewCaption)
{
	CaptionText->SetVisibility(ESlateVisibility::Visible);
	Caption = NewCaption;
	CaptionText->SetText(Caption);
}

void UPropertyRowWidget::HideValue()
{
	ValueText->SetVisibility(ESlateVisibility::Collapsed);
}

void UPropertyRowWidget::HideCaption()
{
	CaptionText->SetVisibility(ESlateVisibility::Hidden);
}

void UPropertyRowWidget::Clear()
{
	HideCaption();
	HideValue();
}
