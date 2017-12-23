// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Logger.h"

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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, msg);
	}
}
void Logger::Error(FString msg)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, msg);
	}
}
void Logger::Warning(FString msg)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, msg);
	}
}
static void Log(float msg) 
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::SanitizeFloat(msg));
	}
}
static void Error(float msg)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(msg));
	}
}
static void Warning(float msg)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::SanitizeFloat(msg));
	}
}