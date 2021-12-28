// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemSlot.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "Data/InventoryData.h"

#include "InventoryAC.generated.h"


UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class TESTELDENRING_API UInventoryAC : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryAC();	

	FEquipmentSlot* GetInventoryItemSlotByEquipmentType(EEquipmentSlot EquipmentSlot);		

	UFUNCTION(BlueprintCallable, meta=(Category="Inventory"))
	TArray<UInventoryItemSlot*> GetInventoryItems(const UDataTable* OwnDataTable);

	/**
	 * @brief Добавление предмета в инвентарь
	 * @param ItemRow Ссылка на строку предмета в таблице
	 * @param Count Количество добавляемых предметов.
	 * @return Объект слота, куда добавили предмет
	 */
	UFUNCTION(BlueprintCallable, meta=(Category="Inventory"))
	UInventoryItemSlot* AddItem(const FDataTableRowHandle& ItemRow, int32 Count);

	/**
	 * @brief Инициализация инвентаря или добавление сразу нескольких предметов
	 * @param Items Массив структур, хранящий предмет и количество
	 * @param bRemoveAllItems Очищать ли инвентарь перед добавление предметов
	 * @return Массив слотов
	 */
	UFUNCTION(BlueprintCallable, meta=(Category="Inventory"))
	TArray<UInventoryItemSlot*> SetItems(TArray<FInventorySlot> Items, bool bRemoveAllItems = true);

	/**
	 * @brief Удаляет предмет из инвентаря
	 * @param ItemRow Ссылка на строку предмета в таблице
	 * @param Count Количество удаляемых предметов
	 * @return Удален ли предмет из инвентаря (может его не было, тогда ложь)
	 */
	UFUNCTION(BlueprintCallable, meta=(Category="Inventory"))
	bool RemoveItem(const FDataTableRowHandle& ItemRow, int32 Count);

	/**
	 * @brief Экипирует или убирает экипировку предмета
	 * @param InventoryItemSlot Объект слота из инвентаря. Если nullptr то снимается экипировка.
	 */
	UFUNCTION(BlueprintCallable, meta=(Category="Inventory"))
	bool SetEquipItem(UInventoryItemSlot* InventoryItemSlot);
	
	/**
	 * @brief Экипирует или убирает экипировку предмета
	 * @param InventoryItemSlot Объект слота из инвентаря. Если nullptr то снимается экипировка.
	 * @param EquipmentSlot Тип слота, куда экипировать
	 */
	UFUNCTION(BlueprintCallable, meta=(Category="Inventory"))
	void SetEquipItemToSlot(UInventoryItemSlot* InventoryItemSlot, EEquipmentSlot EquipmentSlot);

	FItem* GetEmptyEquipmentInfo(EEquipmentSlot EquipmentSlot);

	DECLARE_MULTICAST_DELEGATE_FourParams(FAddedItem, const FDataTableRowHandle& ItemRow, const FItem& Item,
	                                      int32 AddedCount, int32 TotalCount);
	FAddedItem AddedItemEvent;

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FAddedItemToChest, const FDataTableRowHandle& ItemRow, const FItem& Item, int32 Count);
	FAddedItemToChest MoveItemToChest;

	DECLARE_MULTICAST_DELEGATE_FourParams(FRemovedItem, const FDataTableRowHandle& ItemRow, const FItem& Item, int32 RemovedCount, int32 TotalCount);
	FRemovedItem RemovedItemEvent;	

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FEquipItemChanged, EEquipmentSlot EquipmentSlot,	UInventoryItemSlot* FromInventoryItemSlot, UInventoryItemSlot* ToInventoryItemSlot);
	
	FEquipItemChanged EquipItemChanged;

	UFUNCTION(BlueprintCallable, meta=(Category="Inventory"))
	void ClearEquipSlot(EEquipmentSlot EquipmentSlot);

protected:
	virtual void BeginPlay() override;	
	
	UPROPERTY(BlueprintReadWrite)
	TArray<UInventoryItemSlot*> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EEquipmentSlot, FEquipmentSlot> Equipment;
	
private:
	UInventoryItemSlot* FindInventoryItemSlot(const FDataTableRowHandle& ItemRow);
};