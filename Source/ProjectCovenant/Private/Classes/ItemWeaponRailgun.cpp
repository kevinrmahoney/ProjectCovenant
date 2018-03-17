// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Railgun.h"
#include "ItemWeaponRailgun.h"

UItemWeaponRailgun::UItemWeaponRailgun()
{

}

TSubclassOf<class AActor> UItemWeaponRailgun::GetActorClass()
{
	return ItemBlueprint;
}