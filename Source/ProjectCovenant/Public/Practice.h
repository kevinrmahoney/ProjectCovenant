// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Practice.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API APractice : public AGameMode
{
	GENERATED_BODY()

	APractice(const FObjectInitializer& ObjectInitializer);
		
	virtual void StartPlay() override;
};