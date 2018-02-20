// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "HumanController.h"
#include "Deathmatch.generated.h"

class ASubjectZero;

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ADeathmatch : public AGameMode
{
	GENERATED_BODY()
	public:
		UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ASubjectZero> SubjectZeroBlueprint;

		UPROPERTY()
		TArray<ASubjectZero*> Characters;

		ADeathmatch();
		void SpawnPlayer(AHumanController * Controller);

		void KillPlayer(AHumanController * Controller);

		void BeginPlay();
	
	private:
		void PostLogin(APlayerController * NewPlayer);

		TArray<AActor*> SpawnPoints;

		int SpawnCount = 0;
};
