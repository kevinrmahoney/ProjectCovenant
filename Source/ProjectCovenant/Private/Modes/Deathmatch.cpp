// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Deathmatch.h"
#include "Spectator.h"
#include "SubjectZero.h"
#include "BasePlayerState.h"
//#include "HumanController.h"

ADeathmatch::ADeathmatch()
{
	Logger::Log("Mode: Deathmatch");
}


void ADeathmatch::KillPlayer(AHumanController * Controller)
{
	Super::KillPlayer(Controller);
	Logger::Chat("ADeathmatch::Killplayer");
	
	for(auto SomeState : GameState->PlayerArray)
	{
		ABasePlayerState * PlayerState = Cast<ABasePlayerState>(SomeState);
		if(PlayerState && PlayerState->GetKills() >= KillsToWin)
		{
			Logger::Chat(PlayerState->GetName() + " has won!");
		}
	}
}

void ADeathmatch::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	Logger::Chat("ADeathmatch::PostLogin");
}

void ADeathmatch::SpawnPlayer(AHumanController * Controller)
{
	Super::SpawnPlayer(Controller);
	Logger::Chat("ADeathmatch::SpawnPlayer");
}