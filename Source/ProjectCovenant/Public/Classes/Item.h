// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();


public:
	virtual FString ToString();
	int Count = 0;
	bool Equipped = false;
	int ItemID = 100;

	virtual int GetItemID();

};
