// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "InventoryData.generated.h"

class USlateBrushAsset;
UENUM()
enum class EWeaponSubtype
{
	Sword = 0,
	Axe,
	Spear,
	Bow,
	Crossbow,
	Shield
};

UENUM()
enum class EDamageType
{
	Standard = 0,
	Pierce,
	Strike,
	Slash,	
	Standard_Pierce,
	Slash_Pierce,	
};

UENUM()
enum class EScalingValue
{
	NoScaling = 0,
	E,
	D,
	C,	
	B,
	A,	
	S
};

USTRUCT(BlueprintType)
struct TESTELDENRING_API FAttributeScaling
{
	GENERATED_BODY()
public:
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
public:
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
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText AttackName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FPCost;
};

USTRUCT(BlueprintType)
struct TESTELDENRING_API FAttackPower
{
	GENERATED_BODY()
public:	
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
public:
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
	int32 GuardBoost;
};

USTRUCT(BlueprintType)
struct TESTELDENRING_API FDamageNegation
{
	GENERATED_BODY()
public:
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
	float Holy;
};

USTRUCT(BlueprintType)
struct TESTELDENRING_API FResistance
{
	GENERATED_BODY()
public:
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
public:	
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
	
};

/**
 * Weapon item struct
 */
USTRUCT(BlueprintType)
struct TESTELDENRING_API FWeaponItem : public FItem
{
	GENERATED_BODY()
public:	
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
};

/**
 * Armor item struct
 */
USTRUCT(BlueprintType)
struct TESTELDENRING_API FArmorItem : public FItem
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDamageNegation DamageNegation;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FResistance Resistance;
};

/**
 * Consumable item struct
 */
USTRUCT(BlueprintType)
struct TESTELDENRING_API FConsumableItem : public FItem
{
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxCount = 1;

	virtual bool IsConsumable() override
	{
		return true;
	}
};

/**
 * Arrows item struct
 */
USTRUCT(BlueprintType)
struct TESTELDENRING_API FArrowsItem : public FConsumableItem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttackPower AttackPower;
};


class UInventoryItemSlot;

UENUM(BlueprintType, Blueprintable)
enum class EEquipmentSlot : uint8
{
	LHand1 = 0,
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
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryItemSlot* InventoryItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* DataTable;
};