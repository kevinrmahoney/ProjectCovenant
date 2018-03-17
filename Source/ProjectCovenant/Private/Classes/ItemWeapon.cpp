// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "ItemWeapon.h"

UItemWeapon::UItemWeapon()
{

}

void UItemWeapon::SetLastShotTimeStamp()
{
	if(GetWorld())
	{
		LastShotTimeStamp = GetWorld()->GetRealTimeSeconds();
	}
}

FString UItemWeapon::ToString()
{
	return "Weapon";
}