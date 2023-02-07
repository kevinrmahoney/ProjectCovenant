// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Logger.h"
#include "SubjectZero.h"
#include "BaseMode.h"
#include "ProjectCovenantInstance.h"


UProjectCovenantInstance::UProjectCovenantInstance(const FObjectInitializer & ObjectIn)
{
}

void UProjectCovenantInstance::Init()
{
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
	SetSensitivity(Sens);
	SaveConfig();
}

void UProjectCovenantInstance::Volume(float Vol)
{
	SetVolume(Vol);
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

float UProjectCovenantInstance::GetVolume()
{
	return cl_volume;
}

bool UProjectCovenantInstance::SetVolume(float Vol)
{
	cl_volume = FMath::Clamp(Vol, MinVolume, MaxVolume);
	Event_Volume(cl_volume);
	SaveConfig();
	return true;
}

bool UProjectCovenantInstance::Join(FString IPAddress)
{
	if(IPAddress.Equals(""))
	{
		IPAddress = "25.16.209.98";
	}
	else if(IPAddress.Equals("Kevin"))
	{
		IPAddress = "25.16.209.98";
	}
	else if(IPAddress.Equals("Ben"))
	{
		IPAddress = "25.68.54.122";
	}
	else if(IPAddress.Equals("Dave"))
	{
		IPAddress = "25.16.209.98";
	}
	else if(IPAddress.Equals("Mattew"))
	{
		IPAddress = "25.57.118.4";
	}
	else if(IPAddress.Equals("Yousef"))
	{
		IPAddress = "25.53.50.17";
	}

	Logger::Log("Joining server " + IPAddress);
	UWorld * World = GetWorld();
	if(World)
	{
		APlayerController * PlayerController = World->GetFirstPlayerController();
		if(PlayerController)
		{
			PlayerController->ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);
			return true;
		}
	}
	return false;
}

bool UProjectCovenantInstance::Host()
{
	Logger::Log("Hosting server");
	UWorld * World = GetWorld();
	if(World)
	{
		World->ServerTravel("/Game/Maps/TargetRange?listen", true, true);
		return true;
	}
	return false;
}

bool UProjectCovenantInstance::Map(FString Map)
{
	Logger::Log("Changing map to " + Map);
	UWorld * World = GetWorld();
	if(World)
	{
		World->ServerTravel("/Game/Maps/" + Map + "?listen", true, true);
		return true;
	}
	return false;
}

bool UProjectCovenantInstance::Kill()
{
	if(GetFirstLocalPlayerController())
	{
		if(ASubjectZero * SubjectZero = Cast<ASubjectZero>(GetFirstLocalPlayerController()->AcknowledgedPawn))
		{
			ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode());
			if(Mode)
			{
				Mode->DealDamage(nullptr, SubjectZero, 9000.f, nullptr);
			}
		}
	}
	return false;
}

bool UProjectCovenantInstance::Restart()
{
	FString MapName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	Map(MapName);
	return true;
}