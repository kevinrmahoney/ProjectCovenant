// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Shotgun.h"
#include "ItemWeaponShotgun.h"

UItemWeaponShotgun::UItemWeaponShotgun()
{

}

TSubclassOf<class AActor> UItemWeaponShotgun::GetActorClass()
{
	return ItemBlueprint;
}