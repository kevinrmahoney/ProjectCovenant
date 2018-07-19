// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Spectator.h"
#include "UnrealNetwork.h"
#include "Practice.h"
#include "Deathmatch.h"
#include "ProjectCovenantInstance.h"

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

// Called to bind functionality to input
void ASpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	AHumanController * Human = Cast<AHumanController>(GetController());
	if(Human && PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("Yaw", this, &ASpectator::SetYaw);
		PlayerInputComponent->BindAxis("Pitch", this, &ASpectator::SetPitch);
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASpectator::StartMovingUp);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASpectator::StopMovingUp);
		PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASpectator::StartMovingDown);
		PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASpectator::StopMovingDown);
		PlayerInputComponent->BindAction("Forward", IE_Pressed, this, &ASpectator::StartMovingForward);
		PlayerInputComponent->BindAction("Forward", IE_Released, this, &ASpectator::StopMovingForward);
		PlayerInputComponent->BindAction("Backward", IE_Pressed, this, &ASpectator::StartMovingBackward);
		PlayerInputComponent->BindAction("Backward", IE_Released, this, &ASpectator::StopMovingBackward);
		PlayerInputComponent->BindAction("Left", IE_Pressed, this, &ASpectator::StartMovingLeft);
		PlayerInputComponent->BindAction("Left", IE_Released, this, &ASpectator::StopMovingLeft);
		PlayerInputComponent->BindAction("Right", IE_Pressed, this, &ASpectator::StartMovingRight);
		PlayerInputComponent->BindAction("Right", IE_Released, this, &ASpectator::StopMovingRight);
		PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ASpectator::Respawn);
		GetController()->InputComponent = PlayerInputComponent;
	}
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
	if(Role == ROLE_Authority)
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
	UProjectCovenantInstance * Instance = Cast<UProjectCovenantInstance>(GetGameInstance());
	float Sensitivity = 1.f;
	if(Instance)
	{
		Sensitivity = Instance->GetSensitivity();
	}
	AddControllerYawInput(GetWorld()->GetDeltaSeconds() * Set * Sensitivity);
}
void ASpectator::SetPitch(float Set)
{
	UProjectCovenantInstance * Instance = Cast<UProjectCovenantInstance>(GetGameInstance());
	float Sensitivity = 1.f;
	if(Instance)
	{
		Sensitivity = Instance->GetSensitivity();
	}
	AddControllerPitchInput(GetWorld()->GetDeltaSeconds() * Set * Sensitivity);
}

void ASpectator::StartMovingDown()
{
	Down = true;
}

void ASpectator::StopMovingDown()
{
	Down = false;
}

void ASpectator::StartMovingUp()
{
	Up = true;
}

void ASpectator::StopMovingUp()
{
	Up = false;
}

void ASpectator::StartMovingLeft()
{
	Left = true;
}

void ASpectator::StopMovingLeft()
{
	Left = false;
}

void ASpectator::StartMovingRight()
{
	Right= true;
}

void ASpectator::StopMovingRight()
{
	Right = false;
}

void ASpectator::StartMovingForward()
{
	Forward = true;
}

void ASpectator::StopMovingForward()
{
	Forward = false;
}

void ASpectator::StartMovingBackward()
{
	Backward = true;
}

void ASpectator::StopMovingBackward()
{
	Backward = false;
}

void ASpectator::Respawn()
{
	Spawn();
}