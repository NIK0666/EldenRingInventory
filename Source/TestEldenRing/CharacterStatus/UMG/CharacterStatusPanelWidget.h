// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestEldenRing/CharacterStatus/CharacterStatusAC.h"
#include "TestEldenRing/Core/ERPlayerController.h"
#include "CharacterStatusPanelWidget.generated.h"

class UTextBlock;
class UPropertyRowWidget;
/**
 * 
 */
UCLASS()
class TESTELDENRING_API UCharacterStatusPanelWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void Update() const;

protected:
	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* LevelRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* RunesRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* VigorRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* MindRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* EnduranceRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* StrengthRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* DexterityRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* IntelligenceRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* FaithRow;

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* ArcaneRow;
	

	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* HPRow;
	
	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* FPRow;
	
	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* StaminaRow;
	
	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* EquipLoadRow;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* EquipLoadText;
	
	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* DiscoveryRow;
	
	UPROPERTY(meta=(BindWidget))
	UPropertyRowWidget* MemorySlotsRow;

private:
	UPROPERTY(Transient)
	UCharacterStatusAC* CharacterStatusAC;
};
