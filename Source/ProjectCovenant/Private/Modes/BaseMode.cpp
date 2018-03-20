// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HumanController.h"
#include "Spectator.h"
#include "SubjectZero.h"
#include "BasePlayerState.h"
#include "BaseMode.h"

void ABaseMode::BeginPlay()
{
	Super::BeginPlay();
	Logger::Log("Begin BaseMode");
}

void ABaseMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	Logger::Chat("Welcome " + NewPlayer->GetNetOwningPlayer()->GetName());
	Logger::Log(NewPlayer->GetNetOwningPlayer()->GetName() + " has joined the game.");

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

	if(SpawnPoints.Num() != 0)
	{
		SpawnCount = (SpawnCount + 1) % SpawnPoints.Num();
	}
}

/* SpawnPlayer() - Spawns a character at a PlayerStart location.
Spawn location rotates over the course of the game
*/
void ABaseMode::SpawnPlayer(AHumanController * Controller)
{
	Logger::Log("Attempting to spawn player " + Controller->GetNetOwningPlayer()->GetName() + " as a SubjectZero");
	if(Controller)
	{
		if(GetWorld())
		{
			ASubjectZero * NewPawn;
			if(SpawnPoints.Num())
			{
				NewPawn = GetWorld()->SpawnActor<ASubjectZero>(SubjectZeroBlueprint, SpawnPoints[SpawnCount]->GetActorLocation(), SpawnPoints[SpawnCount]->GetActorRotation());
				Logger::Log("Spawned player " + Controller->GetNetOwningPlayer()->GetName() + " at " + NewPawn->GetActorLocation().ToString() + " with rotation " + NewPawn->GetActorRotation().ToString());
			}
			else
			{
				NewPawn = GetWorld()->SpawnActor<ASubjectZero>(SubjectZeroBlueprint, FVector::ZeroVector, FRotator::ZeroRotator);
				Logger::Log("Spawned player " + Controller->GetNetOwningPlayer()->GetName() + " at " + NewPawn->GetActorLocation().ToString() + " with rotation " + NewPawn->GetActorRotation().ToString());
			}
			Characters.Add(NewPawn);
			if(Controller)
			{
				APawn * OldPawn = Controller->GetPawn();
				Controller->Possess(NewPawn);
				if(OldPawn) OldPawn->Destroy();
			}
		}
	}

	if(SpawnPoints.Num() != 0)
	{
		SpawnCount = (SpawnCount + 1) % SpawnPoints.Num();
	}
}

void ABaseMode::KillPlayer(AHumanController * Controller)
{
	Logger::Chat("Killing player " + Controller->GetName());
	if(Controller)
	{
		if(GetWorld())
		{
			if(APawn * OldPawn = Controller->AcknowledgedPawn)
			{
				ASpectator * NewPawn = GetWorld()->SpawnActor<ASpectator>(OldPawn->GetActorLocation(), OldPawn->GetActorRotation());
				Controller->Possess(NewPawn);
				if(ASubjectZero * SubjectZero = Cast<ASubjectZero>(OldPawn))
				{
					Characters.Remove(SubjectZero);
					SubjectZero->Kill();
				}
			}
		}
	}
}

void ABaseMode::DealDamage(ASubjectZero * Shooter, ASubjectZero * Victim, float Damage, AActor * Weapon)
{
	// Multiply raw damage by multiplier
	Damage = Shooter ? Shooter->GetDamageMultiplier() * Damage : Damage;
	bool Killed = false;

	// Deal damage to the victim, returns if the player was killed by the damage
	if(Victim)
	{
		if(AHumanController * VictimController = Cast<AHumanController>(Victim->GetController()))
		{
			if(VictimController && VictimController->GodMode == false)
			{
				Killed = Victim->ReceiveDamage(Damage);
			}
		}
	}

	// Log the damage and if the player was killed by it
	FString ShooterName = Shooter ? Shooter->GetPlayerName().ToString() : "Server";
	FString VictimName = Victim ? Victim->GetPlayerName().ToString() : "Unknown";
	FString WeaponName = Weapon ? Weapon->GetName() : "large fluffy pants";

	Logger::Log(ShooterName + " has dealt " + FString::SanitizeFloat(Damage) + " to " + VictimName + " using " + WeaponName);
	if(Killed) Logger::Log(ShooterName + " has killed " + VictimName + " using " + WeaponName);


	// Obtain the player states for the shooter and the victim
	if(Shooter)
	{
		ABasePlayerState * ShooterPlayerState = Cast<ABasePlayerState>(Shooter->PlayerState);

		// If the player state is successfully obtained, add the damage that was dealt to the player state, and if killed, add the kill
		if(ShooterPlayerState)
		{
			ShooterPlayerState->AddDamageDealt(Damage);
			ShooterPlayerState->DealtDamage(Damage);
			if(Killed) ShooterPlayerState->AddKill(1);
		}
	}
	else
	{
		Logger::Error("Could not cast or obtain shooter's PlayerState");
	}

	if(Victim)
	{
		ABasePlayerState * VictimPlayerState = Cast<ABasePlayerState>(Victim->PlayerState);
		// If the player state is successfully obtained, add the damage that was dealt to the player state, and if killed, add the kill
		if(VictimPlayerState)
		{
			VictimPlayerState->AddDamageTaken(Damage);
			VictimPlayerState->TookDamage(Damage);
			if(Killed) VictimPlayerState->AddDeath(1);
		}
		else
		{
			Logger::Error("Could not cast or obtain victim's PlayerState");
		}
		if(Killed)
		{
			if(AHumanController * HumanController = Cast<AHumanController>(Victim->GetController()))
			{
				KillPlayer(HumanController);
			}
			else
			{
				Logger::Log("Could not kill player " + HumanController->GetName());
			}
		}
	}
}