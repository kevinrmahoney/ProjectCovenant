// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Spectator.h"
#include "UnrealNetwork.h"
#include "Practice.h"
#include "Deathmatch.h"

ASpectator::ASpectator()
{
	if(HasAuthority())
	{
		Logger::Log("Spectator Authority");
	}
	else
	{
		Logger::Log("Spectator Authority");
	}
}

// Input methods
void ASpectator::SetupPlayerInputComponent(class UInputComponent* Input)
{
	Super::SetupPlayerInputComponent(Input);

	Input->BindAction("Use", IE_Pressed, this, &ASpectator::Spawn);
}

/* Spawn() - Spawns a new character. Can only be done on the server */
void ASpectator::Spawn()
{
	Logger::Log("SPAWNING");
	if(Role == ROLE_Authority)
	{
		Logger::Log("Authority");
	}
	else if(Role == ROLE_SimulatedProxy)
	{
		Logger::Log("Simulated");
	}
	else if(Role == ROLE_AutonomousProxy)
	{
		Logger::Log("Autonomous");
	}

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
	Logger::Log("Server Spawn Implementation");
	Spawn();
}

bool ASpectator::Server_Spawn_Validate()
{
	Logger::Log("Server Spawn Validate");
	return true;
}