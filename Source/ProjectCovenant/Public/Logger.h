// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECTCOVENANT_API Logger
{
public:
	Logger();
	~Logger();

	// Send a message to chat
	static void Chat(FString msg);
	static void Chat(float msg);

	// Sends a message to the standard LogTemp
	static void Log(FString msg);
	static void Error(FString msg);
	static void Warning(FString msg);
	static void Log(float msg);
	static void Error(float msg);
	static void Warning(float msg);

	static const float TimeOnScreen;
};