// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Deathmatch.h"
#include "SubjectZero.h"


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
		Logger::Log("Welcome " + GetFullName());
	}
}

/* SpawnPlayer() - Spawns a character at a PlayerStart location. 
	Spawn location rotates over the course of the game
*/
void ADeathmatch::SpawnPlayer()
{
	if(HasAuthority())
	{
		Logger::Log("Respawning...");
		if(GetWorld())
		{
			Logger::Log("Spawning at " + SpawnPoints[SpawnCount]->GetActorLocation().ToString());
			GetWorld()->SpawnActor<ASubjectZero>(SubjectZeroBlueprint, SpawnPoints[SpawnCount]->GetActorLocation(), SpawnPoints[SpawnCount]->GetActorRotation());
		}
	}
	SpawnCount++;
}
