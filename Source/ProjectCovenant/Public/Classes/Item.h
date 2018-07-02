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
	UStaticMeshComponent * Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
};

USTRUCT(BlueprintType)
struct FItemSerialized
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName ItemID;

	UPROPERTY()
	int Count;
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

	UPROPERTY()
	int Count = 0;

	UPROPERTY()
	bool Equipped = false;

	UPROPERTY()
	FName ItemID = TEXT("-1");

	UPROPERTY()
	float LastShotTimeStamp = 0.f;

	UPROPERTY()
	bool IsCoolingDown = 0.f;

	UPROPERTY()
	float Heat = 0.f;

	UPROPERTY()
	float Ammo = 0.f;

	UFUNCTION()
	void SetLastShotTimeStamp(UWorld * World);

	UFUNCTION(BlueprintCallable)
	virtual FName GetItemID();

	// TODO: Write a static Item method that unserializes an FItemSerialized into a UItem, which is an unserialized version to store on computers
	UFUNCTION()
	static UItem * UnserializeItem(FItemSerialized Item);

	// TODO: Write a static Item method that serializes a UItem into a FItemSerialized, which is a serialized version to send over networks
	UFUNCTION()
	static FItemSerialized SerializeItem(UItem * Item);

	UFUNCTION()
	virtual FString ToString();
};