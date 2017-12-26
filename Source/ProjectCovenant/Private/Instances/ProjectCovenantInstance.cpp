// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Logger.h"
#include "ProjectCovenantInstance.h"


UProjectCovenantInstance::UProjectCovenantInstance(const FObjectInitializer & ObjectIn)
{
	Logger::Log("Project Covenant instance constructed.");
}

void UProjectCovenantInstance::Init()
{
	Logger::Log("Project Covenant instance initialized.");
}

bool UProjectCovenantInstance::SetProfileName(FName NewProfileName)
{
	ProfileName = NewProfileName;
	SaveConfig();
	return true;
}

FName UProjectCovenantInstance::GetProfileName()
{
	return ProfileName;
}

void UProjectCovenantInstance::Sensitivity(float Sens)
{
	cl_sensitivity = Sens;
	SaveConfig();
}

float UProjectCovenantInstance::GetSensitivity()
{
	return cl_sensitivity;
}

bool UProjectCovenantInstance::SetSensitivity(float Sens)
{
	cl_sensitivity = Sens;
	SaveConfig();
	return true;
}