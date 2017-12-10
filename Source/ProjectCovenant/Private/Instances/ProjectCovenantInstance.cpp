// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "ProjectCovenantInstance.h"


UProjectCovenantInstance::UProjectCovenantInstance(const FObjectInitializer & ObjectIn)
{
	Log("Project Covenant Instance constructed.");
}

void UProjectCovenantInstance::Init()
{
	Log("Project Covenant Instance initialized.");
}

void UProjectCovenantInstance::Log(FString msg)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, msg);
	}
}

bool UProjectCovenantInstance::SetProfileName(FName NewProfileName)
{
	ProfileName = NewProfileName;
	return true;
}

FName UProjectCovenantInstance::GetProfileName()
{
	return ProfileName;
}