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

	static void Log(FString msg);
};
