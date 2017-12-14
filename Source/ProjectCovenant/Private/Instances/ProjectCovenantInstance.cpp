// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Logger.h"
#include "ProjectCovenantInstance.h"


UProjectCovenantInstance::UProjectCovenantInstance(const FObjectInitializer & ObjectIn)
{
	Logger::Log("Project Covenant Instance constructed.");
}

void UProjectCovenantInstance::Init()
{
	Logger::Log("Project Covenant Instance initialized.");
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

void UProjectCovenantInstance::Sensitivity(float Sens)
{
	cl_sensitivity = Sens;
}

float UProjectCovenantInstance::GetSensitivity()
{
	return cl_sensitivity;
}