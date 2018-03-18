// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/ItemWeapon.h"
#include "ItemWeaponShotgun.generated.h"

class AShotgun;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTCOVENANT_API UItemWeaponShotgun : public UItemWeapon
{
	GENERATED_BODY()
	
public:
	UItemWeaponShotgun();
	FName ItemID = TEXT("3");

	virtual FName GetItemID() override;
};
