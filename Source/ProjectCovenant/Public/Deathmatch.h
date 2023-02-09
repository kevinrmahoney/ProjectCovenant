// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseMode.h"
#include "HumanController.h"
#include "Deathmatch.generated.h"

class ASubjectZero;

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ADeathmatch : public ABaseMode
{
	GENERATED_BODY()

public:
	void Tick(float DeltaTime) override;

	void BeginPlay() override;

	void KillPlayer(AHumanController * Controller) override;

	void SpawnPlayer(AHumanController * Controller) override;

private:
	void PostLogin(APlayerController * NewPlayer) override;

	int KillsToWin = 10;

	float TimeLimit = 600.f;

	float TimeLeft = 600.f;

};
