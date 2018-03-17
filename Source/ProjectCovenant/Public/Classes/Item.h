// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Railgun.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API UItem : public UObject
{
	GENERATED_BODY()


public:

	virtual FString ToString();

	int Count = 0;
	bool Equipped = false;

public:
	UItem();
	virtual TSubclassOf<class AActor> GetActorClass();

private:
	FName BlueprintReference = TEXT("Blueprint'/Game/Blueprints/Weapons/Railgun_BP.Railgun_BP'");
	TSubclassOf<class AActor> ItemBlueprint;
};
