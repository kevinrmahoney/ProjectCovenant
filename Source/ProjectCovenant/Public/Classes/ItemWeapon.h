// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ItemWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API UItemWeapon : public UItem
{
	GENERATED_BODY()
	
public:
	UItemWeapon();

	UFUNCTION()
	void SetLastShotTimeStamp(UWorld * World);

	virtual FString ToString() override;
	int Count = 0;
	int LoadedAmmo = 0;
	float LastShotTimeStamp = 0.f;
	
};
