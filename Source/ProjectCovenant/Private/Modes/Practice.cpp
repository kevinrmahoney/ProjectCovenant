// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Practice.h"
#include "SubjectZero.h"
#include "HumanController.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

APractice::APractice()
{
	Logger::Log("Game mode: Practice");
	/*
	DefaultPawnClass = ASubjectZero::StaticClass();

	// Wizardry involving turning Blueprints into objects. 
	// PlayerHUD is a blueprint that creates widgets (ex. BP_HUD). Make this
	static ConstructorHelpers::FClassFinder <AHUD> PlayerHUD(TEXT("/Game/Blueprints/HUD/PlayerHUD_BP"));
	HUDClass = (UClass*)PlayerHUD.Class;
	*/
}

void APractice::BeginPlay()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), SpawnPoints);
}

void APractice::PostLogin(APlayerController * NewPlayer)
{
	if(HasAuthority())
	{
		Super::PostLogin(NewPlayer);
		if(AHumanController * HumanController = Cast<AHumanController>(NewPlayer))
		{
			Logger::Log("Welcome " + HumanController->GetPlayerName().ToString());
		}
	}
}

/* SpawnPlayer() - Spawns a character at a PlayerStart location.
Spawn location rotates over the course of the game
*/
void APractice::SpawnPlayer()
{
	if(HasAuthority())
	{
		if(GetWorld())
		{
			GetWorld()->SpawnActor<ASubjectZero>(SubjectZeroBlueprint, SpawnPoints[SpawnCount]->GetActorLocation(), SpawnPoints[SpawnCount]->GetActorRotation());
		}
	}
	SpawnCount++;
}

/*
void APractice::StartPlay() 
{
	Super::StartPlay();

	ASubjectZero* Character = Cast<ASubjectZero>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (PlayerHUDClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Mode: Practice"));
	}
}
*/