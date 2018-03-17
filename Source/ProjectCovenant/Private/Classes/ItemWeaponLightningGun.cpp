// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HitscanWeapon.h"
#include "ItemWeaponLightningGun.h"

UItemWeaponLightningGun::UItemWeaponLightningGun()
{

}

TSubclassOf<class AActor> UItemWeaponLightningGun::GetActorClass()
{
	return ItemBlueprint;
}