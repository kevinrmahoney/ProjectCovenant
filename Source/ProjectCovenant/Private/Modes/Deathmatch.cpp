// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Deathmatch.h"
#include "Spectator.h"
#include "SubjectZero.h"
#include "BaseState.h"
#include "BasePlayerState.h"
//#include "HumanController.h"

ADeathmatch::ADeathmatch()
{
	Logger::Log("Mode: Deathmatch");
	ABaseState * State = Cast<ABaseState>(GameState);
	TimeLeft = TimeLimit;
	if(State)
	{
		State->TimeLeft = TimeLeft;
	}
}

void ADeathmatch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ABaseState * State = Cast<ABaseState>(GameState);
	if(State)
	{
		TimeLeft = TimeLeft - DeltaTime;
		State->TimeLeft = TimeLeft;
	}

	if(TimeLeft < 0.f)
	{
		ABasePlayerState * Winner = nullptr;
		for(auto SomeState : GameState->PlayerArray)
		{
			ABasePlayerState * PlayerState = Cast<ABasePlayerState>(SomeState);
			if(!Winner || PlayerState->GetKills() > Winner->GetKills())
			{
				Winner = PlayerState;
			}
			else if(Winner && PlayerState->GetDamageDealt() > Winner->GetDamageDealt())
			{
				Winner = PlayerState;
			}
		}
		
		TimeLeft = TimeLimit;
		if(State)
		{
			State->GameOver();
		}
	}
}

void ADeathmatch::KillPlayer(AHumanController * Controller)
{
	Super::KillPlayer(Controller);
	
	for(auto SomeState : GameState->PlayerArray)
	{
		ABasePlayerState * PlayerState = Cast<ABasePlayerState>(SomeState);
		if(PlayerState && PlayerState->GetKills() >= KillsToWin)
		{
			ABaseState * State = Cast<ABaseState>(GameState);
			if(State)
			{
				State->GameOver();
			}
		}
	}
}

void ADeathmatch::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ADeathmatch::SpawnPlayer(AHumanController * Controller)
{
	Super::SpawnPlayer(Controller);
}