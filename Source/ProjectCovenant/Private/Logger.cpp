// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Logger.h"

const float Logger::TimeOnScreen = 10.f;

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Log(FString msg)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeOnScreen, FColor::Cyan, msg);
	}
}
void Logger::Error(FString msg)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeOnScreen, FColor::Red, msg);
	}
}
void Logger::Warning(FString msg)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeOnScreen, FColor::Yellow, msg);
	}
}
void Logger::Log(float msg) 
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeOnScreen, FColor::Cyan, FString::SanitizeFloat(msg));
	}
}
void Logger::Error(float msg)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeOnScreen, FColor::Red, FString::SanitizeFloat(msg));
	}
}
void Logger::Warning(float msg)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeOnScreen, FColor::Yellow, FString::SanitizeFloat(msg));
	}
}