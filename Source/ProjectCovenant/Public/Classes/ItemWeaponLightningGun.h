// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/ItemWeapon.h"
#include "ItemWeaponLightningGun.generated.h"

class AHitscanWeapon;

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API UItemWeaponLightningGun : public UItemWeapon
{
	GENERATED_BODY()

public:
	UItemWeaponLightningGun();
	virtual TSubclassOf<class AActor> GetActorClass() override;

private:
	const TCHAR * BlueprintReference = TEXT("Class'/Game/Blueprints/Weapons/HitscanWeapon_BP.HitscanWeapon_BP'");
	TSubclassOf<AHitscanWeapon> ItemBlueprint;
};
