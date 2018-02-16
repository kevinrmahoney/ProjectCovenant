// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Practice.generated.h"

class ASubjectZero;

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API APractice : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASubjectZero> SubjectZeroBlueprint;

	APractice();
	void SpawnPlayer();

	void BeginPlay();

private:
	void PostLogin(APlayerController * NewPlayer);

	TArray<AActor*> SpawnPoints;

	int SpawnCount = 0;
	
	/*
	virtual void StartPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (BluePrintProtected = "true"))
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;
	*/
};