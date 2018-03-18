// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Engine/World.h"
#include "ItemWeapon.h"

UItemWeapon::UItemWeapon()
{
}

void UItemWeapon::SetLastShotTimeStamp(UWorld * World)
{
	Logger::Log("Setting last shot time stamp...");
	try
	{
		if(World)
		{
			float Timestamp = World->GetRealTimeSeconds();
			LastShotTimeStamp = Timestamp;
			Logger::Log("Set last shot time stamp to: " + FString::SanitizeFloat(LastShotTimeStamp));
		}
		else
		{
			Logger::Log("GetWorld returned null");
		}
	}
	catch(...)
	{
		Logger::Log("An exception occurred attempting to set the time stamp for firing a weapon");
	}
}

FString UItemWeapon::ToString()
{
	return "Weapon";
}