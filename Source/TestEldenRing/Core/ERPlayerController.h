// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERPlayerController.generated.h"

class UInventoryAC;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TESTELDENRING_API AERPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AERPlayerController(const FObjectInitializer &ObjectInitializer);
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	UInventoryAC* GetInventoryAC() const;

protected:

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	UInventoryAC* InventoryAC = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)	
	TSubclassOf<UInventoryAC> InventoryACClass;
};
