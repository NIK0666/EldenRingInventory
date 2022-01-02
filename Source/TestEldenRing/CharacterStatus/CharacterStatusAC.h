// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterStatusData.h"
#include "TestEldenRing/Core/ERPlayerController.h"
#include "TestEldenRing/Inventory/InventoryAC.h"
#include "TestEldenRing/CharacterStatus/Data/CharacterStatusData.h"
#include "CharacterStatusAC.generated.h"

class UInventoryItemSlot;
/**
 * 
 */
UCLASS()
class TESTELDENRING_API UCharacterStatusAC : public UActorComponent
{
	GENERATED_BODY()
	
public:

	UCharacterStatusAC();	
	
	FCharacterStatus* GetStatus();

	UFUNCTION()
	float GetCurrentWeight();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentFP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentStamina;
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FCharacterStatus BaseStatus;
	
	TArray<UInventoryItemSlot*> MemorySlots;
	

	UInventoryAC* GetInventoryAC();
	
	UPROPERTY(Transient)
	UInventoryAC* InventoryAC;
	
};
