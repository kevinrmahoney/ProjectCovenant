// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Deathmatch.h"
#include "Spectator.h"
#include "SubjectZero.h"
//#include "HumanController.h"

ADeathmatch::ADeathmatch()
{
}

void ADeathmatch::BeginPlay()
{
	Logger::Log("Beginning deathmatch");
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), SpawnPoints);
}

void ADeathmatch::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if(AHumanController * Controller = Cast<AHumanController>(NewPlayer))
	{
		ASpectator * NewPawn = GetWorld()->SpawnActor<ASpectator>(FVector(0.f, 0.f, 100.f), FRotator(0.f, 0.f, 0.f));
		//Controller->Client_Possess(NewPawn);
		Controller->Possess(NewPawn);
	}
	Logger::Log("Welcome " + NewPlayer->GetNetOwningPlayer()->GetName());

}

/* SpawnPlayer() - Spawns a character at a PlayerStart location. 
	Spawn location rotates over the course of the game
*/
void ADeathmatch::SpawnPlayer(AHumanController * Controller)
{
	Logger::Log("Attempting to spawn...");
	if(HasAuthority())
	{
		if(GetWorld())
		{
			ASubjectZero * NewPawn = GetWorld()->SpawnActor<ASubjectZero>(SubjectZeroBlueprint, SpawnPoints[SpawnCount]->GetActorLocation(), SpawnPoints[SpawnCount]->GetActorRotation());
			Characters.Add(NewPawn);
			APawn * OldPawn = Controller->GetPawn();
			Controller->Possess(NewPawn);
			OldPawn->Destroy();
		}
	}
	SpawnCount = (SpawnCount + 1) % SpawnPoints.Num();
}

void ADeathmatch::KillPlayer(AHumanController * Controller)
{
	if(HasAuthority())
	{
		if(GetWorld())
		{
			ASpectator * NewPawn = GetWorld()->SpawnActor<ASpectator>(Controller->GetPawn()->GetActorLocation(), Controller->GetPawn()->GetActorRotation());
			APawn * OldPawn = Controller->GetPawn();
			Controller->Possess(NewPawn);
			if(ASubjectZero * SubjectZero = Cast<ASubjectZero>(OldPawn))
			{
				Characters.Remove(SubjectZero);
				SubjectZero->Kill();
			}
		}
	}
}
