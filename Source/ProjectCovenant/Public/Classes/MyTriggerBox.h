// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MyTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API AMyTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool PrintStatement();

public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	float HealthBoost = 0.25;
	
};
