// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
