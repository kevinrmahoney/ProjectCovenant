// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "HumanController.h"
#include "BaseMode.generated.h"

class ASubjectZero;

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ABaseMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABaseMode();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASubjectZero> SubjectZeroBlueprint;

	UPROPERTY()
	TArray<ASubjectZero*> Characters;

	virtual void SpawnPlayer(AHumanController * Controller);

	virtual void KillPlayer(AHumanController * Controller);

	virtual void BeginPlay();

	virtual void PostLogin(APlayerController * NewPlayer);

private:
	TArray<AActor*> SpawnPoints;

	int SpawnCount = 0;
};
