// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Spectator.h"
#include "UnrealNetwork.h"
#include "Practice.h"
#include "Deathmatch.h"

ASpectator::ASpectator()
{
}

/* Spawn() - Spawns a new character. Can only be done on the server */
void ASpectator::Spawn()
{
	Logger::Log("Trying to Spawn...");
	if(HasAuthority())
	{
		if(ADeathmatch * DeathmatchMode = Cast<ADeathmatch>(GetWorld()->GetAuthGameMode()))
		{
			if(AHumanController * HumanController = Cast<AHumanController>(GetController()))
			{
				DeathmatchMode->SpawnPlayer(HumanController);
			}
		}
	}
	else
	{
		Server_Spawn();
	}
}

void ASpectator::Server_Spawn_Implementation()
{
	Logger::Log("Spawning");
	Spawn();
}

bool ASpectator::Server_Spawn_Validate()
{
	return true;
}