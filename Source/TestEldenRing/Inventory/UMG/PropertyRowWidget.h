// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestEldenRing/Inventory/Data/InventoryData.h"
#include "PropertyRowWidget.generated.h"

class USizeBox;
class UTextBlock;
/**
 * 
 */
UCLASS()
class TESTELDENRING_API UPropertyRowWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
	
	UFUNCTION()
	void SetTextValue(const FText& NewValue);
	
	UFUNCTION()
	void SetStringValue(const FString& NewValue);
	
	UFUNCTION()
	void SetIntValue(const int32& NewValue);
	
	UFUNCTION()
	void SetFloatValue(const float& NewValue);

	UFUNCTION()
	void SetCaption(const FText& NewCaption);
	
	template<typename T>
	void SetEnumValue(T* EnumType, uint8 Value);
	
	template <typename T>
	void SetEnumCaption(T* EnumType, uint8 Value);
	
	void HideValue();
	
	void HideCaption();
	
	void Clear();

protected:

	
	
	UPROPERTY(meta=(BindWidget))
	USizeBox* RootSizeBox;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CaptionText;

	UPROPERTY(EditInstanceOnly)
	bool bIsValueVisible;
	
	UPROPERTY(meta=(BindWidget, EditCondition="bIsValueVisible"))
	UTextBlock* ValueText;

	UPROPERTY(EditInstanceOnly)
	FText Caption;

	UPROPERTY(EditInstanceOnly)
	FText Value;

	UPROPERTY(EditInstanceOnly)
	float WidthMax = 557.f;
};

template <typename T>
void UPropertyRowWidget::SetEnumValue(T* EnumType, uint8 Value)
{
	SetTextValue(EnumType->GetDisplayNameTextByValue(Value));
}

template <typename T>
void UPropertyRowWidget::SetEnumCaption(T* EnumType, uint8 Value)
{
	SetCaption(EnumType->GetDisplayNameTextByValue(Value));
}
