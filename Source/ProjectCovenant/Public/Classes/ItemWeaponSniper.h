// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/ItemWeapon.h"
#include "ItemWeaponSniper.generated.h"

/**
*
*/
UCLASS()
class PROJECTCOVENANT_API UItemWeaponSniper : public UItemWeapon
{
	GENERATED_BODY()

public:
	FName ItemID = TEXT("5");

	virtual FName GetItemID() override;


};