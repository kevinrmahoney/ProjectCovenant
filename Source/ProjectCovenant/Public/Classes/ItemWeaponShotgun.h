// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/ItemWeapon.h"
#include "ItemWeaponShotgun.generated.h"

class AShotgun;

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API UItemWeaponShotgun : public UItemWeapon
{
	GENERATED_BODY()
	
public:
	UItemWeaponShotgun();
	virtual TSubclassOf<class AActor> GetActorClass() override;

private:
	const TCHAR * BlueprintReference = TEXT("Class'/Game/Blueprints/Weapons/Shotgun_BP.Shotgun_BP'");
	TSubclassOf<class AShotgun> ItemBlueprint;
};
