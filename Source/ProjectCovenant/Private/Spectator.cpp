// Fill out your copyright notice in the Description page of Project Settings.

#include "Spectator.h"
#include "UnrealNetwork.h"
#include "Practice.h"
#include "Deathmatch.h"

ASpectator::ASpectator()
{
}

void ASpectator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Left && !Right)
	{
		Movement.Y = -1.f;
	}
	else if(Right && !Left)
	{
		Movement.Y = 1.f;
	}
	else
	{
		Movement.Y = 0.f;
	}

	if(Backward && !Forward)
	{
		Movement.X = -1.f;
	}
	else if(Forward && !Backward)
	{
		Movement.X = 1.f;
	}
	else
	{
		Movement.X = 0.f;
	}

	if(Up && !Down)
	{
		Movement.Z = 1.f;
	}
	else if(Down && !Up)
	{
		Movement.Z = -1.f;
	}
	else
	{
		Movement.Z = 0.f;
	}
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
	if(GetLocalRole() == ROLE_Authority)
	{
		if(ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode()))
		{
			if(AHumanController * HumanController = Cast<AHumanController>(GetController()))
			{
				Mode->SpawnPlayer(HumanController);
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
	Down = Set;
}

void ASpectator::SetSprint(bool Set)
{
	Sprinting = Set;
}

void ASpectator::SetJump(bool Set)
{
	Up = Set;
}

void ASpectator::SetMoveLeft(bool Set)
{
	Left = Set;
}

void ASpectator::SetMoveRight(bool Set)
{
	Right= Set;
}

void ASpectator::SetMoveForward(bool Set)
{
	Forward = Set;
}

void ASpectator::SetMoveBackward(bool Set)
{
	Backward = Set;
}

void ASpectator::SetFire(bool Set)
{
}

void ASpectator::SetSecondaryFire(bool Set)
{

}

void ASpectator::SetInteract(bool Set)
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

void ASpectator::Slot4()
{

}

void ASpectator::Slot5()
{

}

void ASpectator::Slot6()
{

}

void ASpectator::Slot7()
{

}

void ASpectator::Slot8()
{

}

void ASpectator::Slot9()
{

}