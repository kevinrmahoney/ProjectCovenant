// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "ItemWeapon.h"

UItemWeapon::UItemWeapon()
{

}

TSubclassOf<class AActor> UItemWeapon::GetActorClass()
{
	return ItemBlueprint;
}

FString UItemWeapon::ToString()
{
	return "Weapon";
}


