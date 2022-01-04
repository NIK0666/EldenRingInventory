// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControlButtonWidget.generated.h"

class UTextBlock;
class UImage;
class USizeBox;
/**
 * 
 */
UCLASS()
class TESTELDENRING_API UControlButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	
	UFUNCTION()
	void SetDescription(const FText& NewDescription);

protected:
	UPROPERTY(EditInstanceOnly)
	FSlateBrush Button1Brush;

	UPROPERTY(EditInstanceOnly)
	FSlateBrush Button2Brush;

	UPROPERTY(EditInstanceOnly)
	FText Description;

	UPROPERTY(meta=(BindWidget))
	USizeBox* SizeBox1;

	UPROPERTY(meta=(BindWidget))
	USizeBox* SizeBox2;

	UPROPERTY(meta=(BindWidget))
	UImage* Button1Image;

	UPROPERTY(meta=(BindWidget))
	UImage* Button2Image;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* DescriptionText;
};
