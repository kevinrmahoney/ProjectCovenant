// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Deathmatch.h"


ADeathmatch::ADeathmatch()
{
	Logger::Log("Game mode: Deathmatch");
}

void ADeathmatch::PostLogin(APlayerController * NewPlayer)
{
	if(HasAuthority())
	{
		Super::PostLogin(NewPlayer);
		Logger::Log("Welcome " + GetFullName());
	}
}
