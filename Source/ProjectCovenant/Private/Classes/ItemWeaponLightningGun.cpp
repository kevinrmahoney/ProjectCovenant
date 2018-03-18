// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HitscanWeapon.h"
#include "ItemWeaponLightningGun.h"

UItemWeaponLightningGun::UItemWeaponLightningGun()
{
}

FName UItemWeaponLightningGun::GetItemID()
{
	return ItemID;
}