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

void Logger::Chat(FString msg)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeOnScreen, FColor::Cyan, msg);
	}
}

void Logger::Chat(float msg)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeOnScreen, FColor::Cyan, FString::SanitizeFloat(msg));
	}
}

void Logger::Log(FString msg)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *msg);
}
void Logger::Error(FString msg)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *msg);
}
void Logger::Warning(FString msg)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *msg);
}
void Logger::Log(float msg) 
{
	UE_LOG(LogTemp, Log, TEXT("%f"), msg);
}
void Logger::Error(float msg)
{
	UE_LOG(LogTemp, Error, TEXT("%f"), msg);
}
void Logger::Warning(float msg)
{
	UE_LOG(LogTemp, Warning, TEXT("%f"), msg);
}