// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.h"
#include "Inventory.generated.h"

class UItem;

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API UInventory : public UObject
{
	GENERATED_BODY()

public:
	UInventory(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY()
	TArray<UItem*> Items;
	
public:
	void PrintList();
	void AddItem(UItem * Item);
	void RemoveItem(UItem * Item);

	UFUNCTION(BlueprintCallable)
	void SwapItem(int A, int B);

	UFUNCTION(BlueprintCallable)
	UItem * GetItem(int Num);

	UFUNCTION(BlueprintCallable)
	TArray<UItem*> GetItems();

	UFUNCTION(BlueprintCallable)
	bool CheckItem(int Num);
};
