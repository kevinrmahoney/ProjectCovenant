// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HumanController.h"
#include "Spectator.h"
#include "SubjectZero.h"
#include "BasePlayerState.h"
#include "BaseMode.h"

ABaseMode::ABaseMode()
{

}

void ABaseMode::BeginPlay()
{
}

void ABaseMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), SpawnPoints);
	if(AHumanController * Controller = Cast<AHumanController>(NewPlayer))
	{
		ASpectator * NewPawn;
		if(SpawnPoints.Num() > 0)
		{
			NewPawn = GetWorld()->SpawnActor<ASpectator>(SpawnPoints[SpawnCount]->GetActorLocation(), SpawnPoints[SpawnCount]->GetActorRotation());
		}
		else
		{
			NewPawn = GetWorld()->SpawnActor<ASpectator>(FVector::ZeroVector, FRotator::ZeroRotator);
		}
		Controller->Possess(NewPawn);
	}
	Logger::Log("Welcome " + NewPlayer->GetNetOwningPlayer()->GetName());

}

/* SpawnPlayer() - Spawns a character at a PlayerStart location.
Spawn location rotates over the course of the game
*/
void ABaseMode::SpawnPlayer(AHumanController * Controller)
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

void ABaseMode::KillPlayer(AHumanController * Controller)
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

void ABaseMode::DealDamage(ASubjectZero * Shooter, ASubjectZero * Victim, float Damage, AHitscanWeapon * Weapon)
{
	// Deal damage to the victim, returns if the player was killed by the damage
	bool Killed = Victim->ReceiveDamage(Damage);

	// Log the damage and if the player was killed by it
	Logger::Log(Shooter->GetPlayerName().ToString() + " has dealt " + FString::SanitizeFloat(Damage) + " to " + Victim->GetPlayerName().ToString() + " using " + Weapon->GetName());
	if(Killed) Logger::Log(Shooter->GetPlayerName().ToString() + " has killed " + Victim->GetPlayerName().ToString() + " using " + Weapon->GetName());

	// Obtain the player states for the shooter and the victim
	ABasePlayerState * ShooterPlayerState = Cast<ABasePlayerState>(Shooter->PlayerState);
	ABasePlayerState * VictimPlayerState = Cast<ABasePlayerState>(Victim->PlayerState);

	// If the player state is successfully obtained, add the damage that was dealt to the player state, and if killed, add the kill
	if(ShooterPlayerState)
	{
		ShooterPlayerState->AddDamageDealt(Damage);
		if(Killed) ShooterPlayerState->AddKill(1);
	}
	else
	{
		Logger::Error("Could not cast or obtain shooter's PlayerState");
	}

	// If the player state is successfully obtained, add the damage that was dealt to the player state, and if killed, add the kill
	if(VictimPlayerState)
	{
		VictimPlayerState->AddDamageTaken(Damage);
		if(Killed) VictimPlayerState->AddDeath(1);
	}
	else
	{
		Logger::Error("Could not cast or obtain victim's PlayerState");
	}

	if(Killed)
	{
		if(ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode()))
		{
			if(AHumanController * HumanController = Cast<AHumanController>(Victim->GetController()))
			{
				Mode->KillPlayer(HumanController);
			}
		}
	}
}