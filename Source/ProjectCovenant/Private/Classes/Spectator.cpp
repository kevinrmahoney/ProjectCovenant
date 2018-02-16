// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Spectator.h"

ASpectator::ASpectator()
{
	Logger::Log("Spawned as Spectator");
}

// Input methods
void ASpectator::SetupPlayerInputComponent(class UInputComponent* Input)
{
	Super::SetupPlayerInputComponent(Input);

	/*
	// Movement binds
	Input->BindAxis("Yaw", this, &ASpectator::InputYaw);
	Input->BindAxis("Pitch", this, &ASpectator::InputPitch);
	Input->BindAction("Jump", IE_Pressed, this, &ASpectator::InputJumpPress);
	Input->BindAction("Jump", IE_Released, this, &ASpectator::InputJumpRelease);
	Input->BindAction("Sprint", IE_Pressed, this, &ASpectator::InputSprintPress);
	Input->BindAction("Sprint", IE_Released, this, &ASpectator::InputSprintRelease);
	Input->BindAction("Crouch", IE_Pressed, this, &ASpectator::InputCrouchPress);
	Input->BindAction("Crouch", IE_Released, this, &ASpectator::InputCrouchRelease);
	Input->BindAction("Forward", IE_Pressed, this, &ASpectator::InputForwardPress);
	Input->BindAction("Forward", IE_Released, this, &ASpectator::InputForwardRelease);
	Input->BindAction("Backward", IE_Pressed, this, &ASpectator::InputBackwardPress);
	Input->BindAction("Backward", IE_Released, this, &ASpectator::InputBackwardRelease);
	Input->BindAction("Left", IE_Pressed, this, &ASpectator::InputLeftPress);
	Input->BindAction("Left", IE_Released, this, &ASpectator::InputLeftRelease);
	Input->BindAction("Right", IE_Pressed, this, &ASpectator::InputRightPress);
	Input->BindAction("Right", IE_Released, this, &ASpectator::InputRightRelease);
	Input->BindAction("Shoot", IE_Pressed, this, &ASpectator::InputShootPress);
	Input->BindAction("Shoot", IE_Released, this, &ASpectator::InputShootRelease);
	Input->BindAction("PrimaryWeapon", IE_Pressed, this, &ASpectator::InputPrimaryWeaponPress);
	Input->BindAction("SecondaryWeapon", IE_Pressed, this, &ASpectator::InputSecondaryWeaponPress);
	*/
	Input->BindAction("Use", IE_Pressed, this, &ASpectator::Spawn);
}

void ASpectator::Spawn()
{
	Logger::Log("Respawning...");
}