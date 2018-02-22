// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HumanController.h"
#include "ProjectCovenantInstance.h"
#include "SubjectZero.h"
#include "Spectator.h"

AHumanController::AHumanController()
{
}

void AHumanController::BeginPlay()
{
	Super::BeginPlay();
	if(Role == ROLE_AutonomousProxy || Role == ROLE_Authority)
	{
		UGameInstance * Instance = GetGameInstance();

		if(Instance)
		{
			GameInstance = Cast<UProjectCovenantInstance>(Instance);
			if(GameInstance)
			{
				PlayerName = GameInstance->GetProfileName();
				Server_Set_Name(PlayerName);
			}
		}
	}
}

void AHumanController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SubjectZero = Cast<ASubjectZero>(AcknowledgedPawn);
	Spectator = Cast<ASpectator>(AcknowledgedPawn);
}

void AHumanController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(InputComponent)
	{
		InputComponent->BindAxis("Yaw", this, &AHumanController::InputYaw);
		InputComponent->BindAxis("Pitch", this, &AHumanController::InputPitch);
		InputComponent->BindAction("Jump", IE_Pressed, this, &AHumanController::InputJumpPress);
		InputComponent->BindAction("Jump", IE_Released, this, &AHumanController::InputJumpRelease);
		InputComponent->BindAction("Sprint", IE_Pressed, this, &AHumanController::InputSprintPress);
		InputComponent->BindAction("Sprint", IE_Released, this, &AHumanController::InputSprintRelease);
		InputComponent->BindAction("Crouch", IE_Pressed, this, &AHumanController::InputCrouchPress);
		InputComponent->BindAction("Crouch", IE_Released, this, &AHumanController::InputCrouchRelease);
		InputComponent->BindAction("Forward", IE_Pressed, this, &AHumanController::InputForwardPress);
		InputComponent->BindAction("Forward", IE_Released, this, &AHumanController::InputForwardRelease);
		InputComponent->BindAction("Backward", IE_Pressed, this, &AHumanController::InputBackwardPress);
		InputComponent->BindAction("Backward", IE_Released, this, &AHumanController::InputBackwardRelease);
		InputComponent->BindAction("Left", IE_Pressed, this, &AHumanController::InputLeftPress);
		InputComponent->BindAction("Left", IE_Released, this, &AHumanController::InputLeftRelease);
		InputComponent->BindAction("Right", IE_Pressed, this, &AHumanController::InputRightPress);
		InputComponent->BindAction("Right", IE_Released, this, &AHumanController::InputRightRelease);
		InputComponent->BindAction("Shoot", IE_Pressed, this, &AHumanController::InputShootPress);
		InputComponent->BindAction("Shoot", IE_Released, this, &AHumanController::InputShootRelease);
		InputComponent->BindAction("PrimaryWeapon", IE_Pressed, this, &AHumanController::InputPrimaryWeaponPress);
		InputComponent->BindAction("SecondaryWeapon", IE_Pressed, this, &AHumanController::InputSecondaryWeaponPress);
		InputComponent->BindAction("Use", IE_Pressed, this, &AHumanController::InputUsePress);
	}
}

void AHumanController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

	if(ASubjectZero * Test = Cast<ASubjectZero>(AcknowledgedPawn))
	{
		Logger::Log("Spawning as SubjectZero");
		SubjectZero = Test;
		Spectator = nullptr;
	} 
	else if(ASpectator * Test = Cast<ASpectator>(AcknowledgedPawn))
	{
		Logger::Log("Spawning as Spectator");
		Spectator = Test;
		SubjectZero = nullptr;
	}
}

void AHumanController::UnPossess()
{
	Super::UnPossess();
}

ASubjectZero * AHumanController::GetSubjectZero()
{
	return SubjectZero;
}

void AHumanController::Server_Set_Name_Implementation(FName NewName)
{
	PlayerName = NewName;
}

bool AHumanController::Server_Set_Name_Validate(FName Name)
{
	return true;
}


void AHumanController::InputYaw(float Value) 
{
	if(SubjectZero)
	{
		SubjectZero->SetYaw(Value * GameInstance->GetSensitivity());
	}
	if(Spectator)
	{
		Spectator->SetYaw(Value * GameInstance->GetSensitivity());
	}
}
void AHumanController::InputPitch(float Value) 
{
	if(SubjectZero)
	{
		SubjectZero->SetPitch(Value * GameInstance->GetSensitivity());
	}
	else if(Spectator)
	{
		Spectator->SetPitch(Value * GameInstance->GetSensitivity());
	}
}
void AHumanController::InputForwardPress() 
{ 
	if(SubjectZero)
	{
		SubjectZero->SetMoveForward(true);
	}
	else if(Spectator)
	{
		Spectator->SetMoveForward(true);
	}
}
void AHumanController::InputForwardRelease() 
{ 
	if(SubjectZero)
	{
		SubjectZero->SetMoveForward(false);
	}
	else if(Spectator)
	{
		Spectator->SetMoveForward(false);
	}
}
void AHumanController::InputBackwardPress() 
{ 
	if(SubjectZero)
	{
		SubjectZero->SetMoveBackward(true);
	}
	else if(Spectator)
	{
		Spectator->SetMoveBackward(true);
	}
}
void AHumanController::InputBackwardRelease() 
{ 
	if(SubjectZero)
	{
		SubjectZero->SetMoveBackward(false);
	}
	else if(Spectator)
	{
		Spectator->SetMoveBackward(false);
	}
}
void AHumanController::InputLeftPress() 
{ 
	if(SubjectZero)
	{
		SubjectZero->SetMoveLeft(true);
	}
	else if(Spectator)
	{
		Spectator->SetMoveLeft(true);;
	}
}
void AHumanController::InputLeftRelease()
{
	if(SubjectZero)
	{
		SubjectZero->SetMoveLeft(false);
	}
	else if(Spectator)
	{
		Spectator->SetMoveLeft(false);
	}
}
void AHumanController::InputRightPress() 
{
	if(SubjectZero)
	{
		SubjectZero->SetMoveRight(true);
	}
	else if(Spectator)
	{
		Spectator->SetMoveRight(true);
	}
}
void AHumanController::InputRightRelease() 
{ 
	if(SubjectZero)
	{
		SubjectZero->SetMoveRight(false);
	}
	else if(Spectator)
	{
		Spectator->SetMoveRight(false);
	}
}
void AHumanController::InputJumpPress()
{
	if(SubjectZero)
	{
		SubjectZero->SetJump(true);
	}
	else if(Spectator)
	{
		Spectator->SetJump(true);
	}
}
void AHumanController::InputJumpRelease()
{
	if(SubjectZero)
	{
		SubjectZero->SetJump(false);
	}
	else if(Spectator)
	{
		Spectator->SetJump(false);
	}
}
void AHumanController::InputSprintPress()
{
	if(SubjectZero)
	{
		SubjectZero->SetSprint(true);
	}
	else if(Spectator)
	{
		Spectator->SetSprint(true);
	}
}
void AHumanController::InputSprintRelease()
{
	if(SubjectZero)
	{
		SubjectZero->SetSprint(false);
	}
	else if(Spectator)
	{
		Spectator->SetSprint(false);
	}
}
void AHumanController::InputCrouchPress()
{
	if(SubjectZero)
	{
		SubjectZero->SetCrouch(true);
	}
	else if(Spectator)
	{
		Spectator->SetCrouch(true);
	}
}
void AHumanController::InputCrouchRelease()
{
	if(SubjectZero)
	{
		SubjectZero->SetCrouch(false);
	}
	else if(Spectator)
	{
		Spectator->SetCrouch(false);
	}
}
void AHumanController::InputShootPress()
{
	if(SubjectZero)
	{
		SubjectZero->SetFire(true);
	}
	else if(Spectator)
	{
		Spectator->SetFire(true);
	}
}
void AHumanController::InputShootRelease()
{
	if(SubjectZero)
	{
		SubjectZero->SetFire(false);
	}
	else if(Spectator)
	{
		Spectator->SetFire(false);
	}
}
void AHumanController::InputPrimaryWeaponPress()
{
	if(SubjectZero)
	{
		SubjectZero->Slot0();
	}
	else if(Spectator)
	{
		Spectator->Slot0();
	}
}
void AHumanController::InputSecondaryWeaponPress()
{
	if(SubjectZero)
	{
		SubjectZero->Slot1();
	}
	else if(Spectator)
	{
		Spectator->Slot1();
	}
}
void AHumanController::InputThirdaryWeaponPress()
{
	if(SubjectZero)
	{
		SubjectZero->Slot2();
	}
	else if(Spectator)
	{
		Spectator->Slot2();
	}
}

void AHumanController::InputUsePress()
{
	if(SubjectZero)
	{
		SubjectZero->SetUse(true);
	}
	else if(Spectator)
	{
		Spectator->SetUse(true);
	}
}

FName AHumanController::GetPlayerName() const { return PlayerName; }