// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Deathmatch.h"
#include "Spectator.h"
#include "SubjectZero.h"
//#include "HumanController.h"

ADeathmatch::ADeathmatch()
{
	Logger::Log("Game mode: Deathmatch");
}

void ADeathmatch::BeginPlay()
{
	Logger::Log("Beginning deathmatch");
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), SpawnPoints);

	for(auto& SpawnPoint : SpawnPoints)
	{
		Logger::Log(SpawnPoint->GetActorLocation().ToString());
	}
	Logger::Log("There are " + FString::FromInt(SpawnPoints.Num()) + " spawn points on this map, in the following locations:");
}

void ADeathmatch::PostLogin(APlayerController * NewPlayer)
{
	if(HasAuthority())
	{
		Super::PostLogin(NewPlayer);
		if(AHumanController * Controller = Cast<AHumanController>(NewPlayer))
		{
			ASpectator * NewPawn = GetWorld()->SpawnActor<ASpectator>();
			Controller->Possess(NewPawn);
		}
		Logger::Log("Welcome " + GetFullName());
	}
}

/* SpawnPlayer() - Spawns a character at a PlayerStart location. 
	Spawn location rotates over the course of the game
*/
void ADeathmatch::SpawnPlayer(AHumanController * Controller)
{
	if(HasAuthority())
	{
		Logger::Log("Respawning...");
		if(GetWorld())
		{
			Logger::Log("Spawning at " + SpawnPoints[SpawnCount]->GetActorLocation().ToString());
			ASubjectZero * NewPawn = GetWorld()->SpawnActor<ASubjectZero>(SubjectZeroBlueprint, SpawnPoints[SpawnCount]->GetActorLocation(), SpawnPoints[SpawnCount]->GetActorRotation());
			Characters.Add(NewPawn);
			APawn * OldPawn = Controller->GetPawn();
			Controller->UnPossess();
			Controller->Possess(NewPawn);
			OldPawn->Destroy();
		}
	}
	SpawnCount = (SpawnCount + 1) % SpawnPoints.Num();
	Logger::Log(FString::FromInt(Characters.Num()));
}

void ADeathmatch::KillPlayer(AHumanController * Controller)
{
	if(HasAuthority())
	{
		if(GetWorld())
		{
			ASpectator * NewPawn = GetWorld()->SpawnActor<ASpectator>(Controller->GetPawn()->GetActorLocation(), Controller->GetPawn()->GetActorRotation());
			APawn * OldPawn = Controller->GetPawn();
			if(ASubjectZero * SubjectZero = Cast<ASubjectZero>(OldPawn))
			{
				Characters.Remove(SubjectZero);
			}
			Controller->UnPossess();
			Controller->Possess(NewPawn);
			OldPawn->Destroy();
		}
	}
}
