// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/ItemWeapon.h"
#include "ItemWeaponRailgun.generated.h"

class ARailgun;

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API UItemWeaponRailgun : public UItemWeapon
{
	GENERATED_BODY()

public:
	UItemWeaponRailgun();
	virtual TSubclassOf<class AActor> GetActorClass() override;

private:
	const TCHAR * BlueprintReference = TEXT("Class'/Game/Blueprints/Weapons/Railgun_BP.Railgun_BP'");
	TSubclassOf<class ARailgun> ItemBlueprint;
	
};
