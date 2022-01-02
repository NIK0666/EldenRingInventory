// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "InventoryData.generated.h"

class USlateBrushAsset;
UENUM()
enum class EWeaponSubtype : uint8
{
	Sword = 0		UMETA(DisplayName = "Sword"),
	Axe				UMETA(DisplayName = "Axe"),
	Spear			UMETA(DisplayName = "Spear"),
	Bow				UMETA(DisplayName = "Bow"),
	Crossbow		UMETA(DisplayName = "Crossbow"),
	Shield			UMETA(DisplayName = "Shield"),
	Fists			UMETA(DisplayName = "Fists")
};

UENUM()
enum class EDamageType: uint8
{
	Standard = 0		UMETA(DisplayName = "Standard"),
	Pierce				UMETA(DisplayName = "Pierce"),
	Strike				UMETA(DisplayName = "Strike"),
	Slash				UMETA(DisplayName = "Slash"),
	Standard_Pierce		UMETA(DisplayName = "Standard / Pierce"),
	Slash_Pierce		UMETA(DisplayName = "Slash / Pierce")
};

UENUM()
enum class EScalingValue: uint8
{
	NoScaling = 0	UMETA(DisplayName = "-"),
	E				UMETA(DisplayName = "E"),
	D				UMETA(DisplayName = "D"),
	C				UMETA(DisplayName = "C"),
	B				UMETA(DisplayName = "B"),
	A				UMETA(DisplayName = "A"),
	S				UMETA(DisplayName = "S")
};

UENUM()
enum class EItemType
{
	Item = 0,
	Weapon,
	Armor,
	Arrows,
	Bolts,
	Amulet,
	Consumable
};

UENUM()
enum class EItemEffectType: uint8
{
	None = 0,
	MaxHP,
	MaxFP,
	RegenHP,
	MaxEquipLoad
};


USTRUCT(BlueprintType)
struct TESTELDENRING_API FItemEffect
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemEffectType EffectType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};

USTRUCT(BlueprintType)
struct TESTELDENRING_API FAttributeScaling
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EScalingValue Str;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EScalingValue Dex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EScalingValue Int;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EScalingValue Fai;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EScalingValue Arc;
};

USTRUCT(BlueprintType)
struct TESTELDENRING_API FAttributeRequired
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Str;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Dex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Int;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Fai;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Arc;
};

USTRUCT(BlueprintType)
struct TESTELDENRING_API FSuperAttack
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText AttackName = FText::FromString("No skill");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FPCost;
};

USTRUCT(BlueprintType)
struct TESTELDENRING_API FAttackPower
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Physical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Magic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Lightning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Holy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Critical;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite) //TODO Staffs attack power
	// int32 SorceryScaling;
};

USTRUCT(BlueprintType)
struct TESTELDENRING_API FGuardedDamageNegation
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Physical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Magic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lightning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Holy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GuardBoost;
};

USTRUCT(BlueprintType)
struct TESTELDENRING_API FDamageNegation
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Physical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Strike;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Slash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Pierce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Magic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lightning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Holy;
};

USTRUCT(BlueprintType)
struct TESTELDENRING_API FResistance
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Immunity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Robustness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Focus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Death;
};




/**
 * Base item struct
 */
USTRUCT(BlueprintType)
struct TESTELDENRING_API FItem: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DetailsTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DetailsDescription;

	virtual bool IsConsumable()
	{
		return false;
	}

	virtual EItemType ItemType()
	{		
		return EItemType::Item;
	}
};

/**
 * Weapon item struct
 */
USTRUCT(BlueprintType)
struct TESTELDENRING_API FWeaponItem : public FItem
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponSubtype WeaponSubtype;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDamageType DamageType;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaminaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSuperAttack SuperAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttackPower AttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuardedDamageNegation GuardedDamageNegation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeScaling AttributeScaling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeRequired AttributeRequired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemEffect> PassiveEffects;

	virtual EItemType ItemType() override
	{		
		return EItemType::Weapon;
	}
};

/**
 * Armor item struct
 */
USTRUCT(BlueprintType)
struct TESTELDENRING_API FArmorItem : public FItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDamageNegation DamageNegation;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FResistance Resistance;

	virtual EItemType ItemType() override
	{		
		return EItemType::Armor;
	}
};

/**
 * Base Consumable item struct (Abstract)
 */
USTRUCT(BlueprintType)
struct TESTELDENRING_API FBaseConsumableItem : public FItem
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxCount = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStoredCount = 600;

	virtual bool IsConsumable() override
	{
		return true;
	}

	virtual EItemType ItemType() override
	{		
		return EItemType::Consumable;
	}
};

/**
 * Arrows item struct
 */
USTRUCT(BlueprintType)
struct TESTELDENRING_API FArrowsItem : public FBaseConsumableItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttackPower AttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemEffect> PassiveEffects;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDamageType DamageType;

	virtual EItemType ItemType() override
	{		
		return EItemType::Arrows;
	}
};

/**
 * Arrows item struct
 */
USTRUCT(BlueprintType)
struct TESTELDENRING_API FAmuletItem : public FItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemEffect> ItemEffects;

	virtual EItemType ItemType() override
	{		
		return EItemType::Amulet;
	}
};

/**
 * Consumable item struct
 */
USTRUCT(BlueprintType)
struct TESTELDENRING_API FConsumableItem : public FBaseConsumableItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FPCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemEffect> ItemEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeScaling AttributeScaling;
};


class UInventoryItemSlot;

UENUM(BlueprintType, Blueprintable)
enum class EEquipmentSlot : uint8
{
	None = 0,
	LHand1,
	LHand2,
	LHand3,
	RHand1,
	RHand2,
	RHand3,
	Arrows1,
	Arrows2,
	Bolts1,
	Bolts2,
	Helm,
	Armor,
	Gloves,
	Boots,
	Amulet1,
	Amulet2,
	Consumables1,
	Consumables2,
	Consumables3,
	Consumables4,
	Consumables5,
	Consumables6,
	Consumables7,
	Consumables8,
	Consumables9,
	Consumables10
};

/**
 * Equipment slot struct
 */
USTRUCT(BlueprintType)
struct TESTELDENRING_API FEquipmentSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryItemSlot* InventoryItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* DataTable;
};