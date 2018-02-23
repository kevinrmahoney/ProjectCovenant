// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Spectator.h"
#include "UnrealNetwork.h"
#include "Practice.h"
#include "Deathmatch.h"

ASpectator::ASpectator()
{
}

void ASpectator::Tick(float DeltaTime)
{
	Move();
}

void ASpectator::Move()
{
	if(Controller)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FVector Distance = Movement * (Sprinting ? 3.f : 1.f);
		AddMovementInput(Rotation.RotateVector(Distance), 1.f);
	}
}

void ASpectator::Server_Move_Implementation()
{
	Logger::Log("Spawning");
	Move();
}

bool ASpectator::Server_Move_Validate()
{
	return true;
}

/* Spawn() - Spawns a new character. Can only be done on the server */
void ASpectator::Spawn()
{
	Logger::Log("Trying to Spawn...");
	if(HasAuthority())
	{
		if(ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode()))
		{
			if(AHumanController * HumanController = Cast<AHumanController>(GetController()))
			{
				Mode->SpawnPlayer(HumanController);
			}
		}
		else
		{
			Logger::Chat("Whoops");
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


void ASpectator::SetYaw(float Set)
{
	AddControllerYawInput(GetWorld()->GetDeltaSeconds() * Set);
}
void ASpectator::SetPitch(float Set)
{
	AddControllerPitchInput(GetWorld()->GetDeltaSeconds() * Set);
}

void ASpectator::SetCrouch(bool Set)
{
	Movement.Z -= Set ? 1.f : -1.f;
}

void ASpectator::SetSprint(bool Set)
{
	Sprinting = Set;
}

void ASpectator::SetJump(bool Set)
{
	Movement.Z += Set ? 1.f : -1.f;
}

void ASpectator::SetMoveLeft(bool Set)
{
	Movement.Y -= Set ? 1.f : -1.f;
}

void ASpectator::SetMoveRight(bool Set)
{
	Movement.Y += Set ? 1.f : -1.f;
}

void ASpectator::SetMoveForward(bool Set)
{
	Movement.X += Set ? 1.f : -1.f;
}

void ASpectator::SetMoveBackward(bool Set)
{
	Movement.X -= Set ? 1.f : -1.f;
}

void ASpectator::SetFire(bool Set)
{
}

void ASpectator::SetSecondaryFire(bool Set)
{

}

void ASpectator::SetUse(bool Set)
{
	Spawn();
}

void ASpectator::Slot0()
{

}

void ASpectator::Slot1()
{

}

void ASpectator::Slot2()
{

}

void ASpectator::Slot3()
{

}