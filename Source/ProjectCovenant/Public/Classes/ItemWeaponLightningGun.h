// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/ItemWeapon.h"
#include "ItemWeaponLightningGun.generated.h"

class AHitscanWeapon;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTCOVENANT_API UItemWeaponLightningGun : public UItemWeapon
{
	GENERATED_BODY()

public:
	UItemWeaponLightningGun();
	FName ItemID = TEXT("1");

	virtual FName GetItemID() override;
};
