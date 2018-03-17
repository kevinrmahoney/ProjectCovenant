// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/ItemWeapon.h"
#include "ItemWeaponRailgun.generated.h"

class ARailgun;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTCOVENANT_API UItemWeaponRailgun : public UItemWeapon
{
	GENERATED_BODY()

public:
	UItemWeaponRailgun();
	virtual TSubclassOf<class AActor> GetActorClass() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ARailgun> ItemBlueprint;
};
