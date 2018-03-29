// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D * Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
};

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
	FName ItemID = TEXT("-1");

	UFUNCTION(BlueprintCallable)
	virtual FName GetItemID();

};
