// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemWeapon.h"
#include "ItemWeaponRifle.generated.h"

/**
*
*/
UCLASS()
class PROJECTCOVENANT_API UItemWeaponRifle : public UItemWeapon
{
	GENERATED_BODY()

public:
	FName ItemID = TEXT("4");

	virtual FName GetItemID() override;


};