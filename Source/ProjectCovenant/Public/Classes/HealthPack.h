// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "HealthPack.generated.h"

class ASubjectZero;

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API AHealthPack : public ATriggerBox
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintPure, BlueprintCallable)
			bool AddHealth(ASubjectZero * player, float HealthBoost);

	public: 
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealPercentage")
			float HealthBoost = 0.25f;
};