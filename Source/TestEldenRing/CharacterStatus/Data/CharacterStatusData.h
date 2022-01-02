// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStatusData.generated.h"

UENUM()
enum class EEquipLoad : uint8
{
	LightLoad = 0	UMETA(DisplayName = "Light Load"),
	MedLoad				UMETA(DisplayName = "Med. Load"),
	HeavyLoad			UMETA(DisplayName = "Heavy Load")
};

USTRUCT(BlueprintType)
struct TESTELDENRING_API FCharacterStatus
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Runes;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Vigor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Mind;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Endurance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Strength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Dexterity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Intelligence;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Faith;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Arcane;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HP_Max;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FP_Max;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Stamina;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Stamina_Max;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EquipLoadWeight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipLoad EquipLoad;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Discovery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MemorySlots;
};