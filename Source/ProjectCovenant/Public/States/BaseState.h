// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BaseState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ABaseState : public AGameState
{
	GENERATED_BODY()

public:
	ABaseState();
	
	void BeginPlay() override;

	void Tick(float DeltaTime) override;
	
};
