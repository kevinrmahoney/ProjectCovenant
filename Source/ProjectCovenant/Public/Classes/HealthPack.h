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
class PROJECTCOVENANT_API AHealthPack : public AActor
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintPure, BlueprintCallable)
		bool AddHealth(ASubjectZero * player);

	public: 
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		float HealthBoostPercentage = 0.25f;
};