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
		//AddActorLocalOffset(Rotation.RotateVector(Movement.GetSafeNormal()));
		//AddActorLocalOffset(Rotation.RotateVector(Movement));
		FVector Distance = Movement * (Sprinting ? 3.f : 1.f);
		Logger::Chat(Distance.ToString());
		AddMovementInput(Rotation.RotateVector(Distance), 1.f);
	}
	else
	{
		Logger::Error("No controller");
	}
	if(!HasAuthority())
	{
		Server_Move();
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


void ASpectator::LookRight(float Set)
{
	AddControllerYawInput(GetWorld()->GetDeltaSeconds() * Set);
}
void ASpectator::LookUp(float Set)
{
	AddControllerPitchInput(GetWorld()->GetDeltaSeconds() * Set);
}

void ASpectator::Crouch(bool Set)
{
	Movement.Z -= Set ? 1.f : -1.f;
}

void ASpectator::Sprint(bool Set)
{
	Sprinting = Set;
}

void ASpectator::Jump(bool Set)
{
	Movement.Z += Set ? 1.f : -1.f;
}

void ASpectator::MoveLeft(bool Set)
{
	Movement.Y -= Set ? 1.f : -1.f;
}

void ASpectator::MoveRight(bool Set)
{
	Movement.Y += Set ? 1.f : -1.f;
}

void ASpectator::MoveForward(bool Set)
{
	Movement.X += Set ? 1.f : -1.f;
}

void ASpectator::MoveBackward(bool Set)
{
	Movement.X -= Set ? 1.f : -1.f;
}

void ASpectator::Fire(bool Set)
{
}

void ASpectator::SecondaryFire(bool Set)
{

}

void ASpectator::Use(bool Set)
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