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

	ADeathmatch();

	void Tick(float DeltaTime) override;

	void KillPlayer(AHumanController * Controller) override;

	void SpawnPlayer(AHumanController * Controller) override;

private:
	void PostLogin(APlayerController * NewPlayer) override;

	int KillsToWin = 30;

	float TimeLimit = 600.f;

	float TimeLeft;

};
