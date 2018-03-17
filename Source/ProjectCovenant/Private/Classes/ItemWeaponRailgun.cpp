// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Railgun.h"
#include "ItemWeaponRailgun.h"

UItemWeaponRailgun::UItemWeaponRailgun()
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> Blueprint(BlueprintReference);
	if(Blueprint.Object)
	{
		ItemBlueprint = (UClass*)Blueprint.Object->GeneratedClass;
	}
	else
	{
		FString BP_Name = *BlueprintReference + "";
		Logger::Error("ERROR: Could not find blueprint class (" + BP_Name + ") for cpp class " + GetClass()->GetName());
	}
}

TSubclassOf<class AActor> UItemWeaponRailgun::GetActorClass()
{
	return ItemBlueprint;
}