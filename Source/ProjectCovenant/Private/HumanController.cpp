// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HumanController.h"
#include "ProjectCovenantInstance.h"
#include "SubjectZero.h"
#include "BaseState.h"
#include "BasePlayerState.h"
#include "ScoreboardWidget.h"
#include "Blueprint/UserWidget.h"
#include "UnrealNetwork.h"
#include "Spectator.h"
#include "Weapon.h"

AHumanController::AHumanController()
{
}

void AHumanController::BeginPlay()
{
	Super::BeginPlay();
	Logger::Log("Begin: " + GetName());

	if(IsLocalController())
	{
		UGameInstance * Instance = GetGameInstance();
		GameInstance = Cast<UProjectCovenantInstance>(Instance);
		if(GameInstance)
		{
			PlayerName = GameInstance->GetProfileName();
			Server_Set_Name(PlayerName);
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
		InputComponent->BindAction("Burst", IE_DoubleClick, this, &AHumanController::InputBurst);
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
		InputComponent->BindAction("Fire", IE_Pressed, this, &AHumanController::InputShootPress);
		InputComponent->BindAction("Fire", IE_Released, this, &AHumanController::InputShootRelease);
		InputComponent->BindAction("SecondaryFire", IE_Pressed, this, &AHumanController::InputSecondaryFirePress);
		InputComponent->BindAction("SecondaryFire", IE_Released, this, &AHumanController::InputSecondaryFireRelease);
		InputComponent->BindAction("Slot 1", IE_Pressed, this, &AHumanController::InputSlot0);
		InputComponent->BindAction("Slot 2", IE_Pressed, this, &AHumanController::InputSlot1);
		InputComponent->BindAction("Slot 3", IE_Pressed, this, &AHumanController::InputSlot2);
		InputComponent->BindAction("Use", IE_Pressed, this, &AHumanController::InputInteractPress);
		InputComponent->BindAction("Scoreboard", IE_Pressed, this, &AHumanController::InputScoreboardPress);
		InputComponent->BindAction("Scoreboard", IE_Released, this, &AHumanController::InputScoreboardRelease);
		InputComponent->BindAction("Reload", IE_Pressed, this, &AHumanController::InputReload);
		InputComponent->BindAction("QuickInventory", IE_Pressed, this, &AHumanController::InputQuickOpenInventory);
		InputComponent->BindAction("QuickInventory", IE_Released, this, &AHumanController::InputQuickCloseInventory);
	}
}

void AHumanController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AHumanController::God(FString Set = "")
{
	if(GetLocalRole() == ROLE_AutonomousProxy)
	{
		Server_God(Set);
	}

	if(Set.ToLower() == "on")
	{
		GodMode = true;
	}
	else if(Set.ToLower() == "off")
	{
		GodMode = false;
	}
	else if(Set == "")
	{
		GodMode = !GodMode;
	}
	else
	{
		Logger::Chat("usage: God [optional:<on|off>,default:toggle,]");
	}
}

void AHumanController::Server_God_Implementation(const FString & Set)
{
	God(Set);
}

bool AHumanController::Server_God_Validate(const FString & Set)
{
	return true;
}

void AHumanController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if(ASubjectZero * NewSubjectZero = Cast<ASubjectZero>(AcknowledgedPawn))
	{
		Logger::Log("Spawning as SubjectZero");
		SubjectZero = NewSubjectZero;
		Spectator = nullptr;
		UpdateHUD();
	}
	else if(ASpectator * NewSpectator = Cast<ASpectator>(AcknowledgedPawn))
	{
		Logger::Log("Spawning as Spectator");
		Spectator = NewSpectator;
		SubjectZero = nullptr;
		UpdateHUD();
	}
}

void AHumanController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AHumanController::SetPawn(APawn * NewPawn)
{
	Super::SetPawn(NewPawn);

	if(IsLocalController())
	{
		InitializeHUD();
	}
}

ASubjectZero * AHumanController::GetSubjectZero()
{
	ASubjectZero * NewSubjectZero = Cast<ASubjectZero>(AcknowledgedPawn);
	return NewSubjectZero;
}

void AHumanController::Server_Set_Name_Implementation(FName NewName)
{
	PlayerName = NewName;
	if(ABasePlayerState * BasePlayerState = Cast<ABasePlayerState>(PlayerState))
	{
		BasePlayerState->SetName(NewName.ToString());
	}
}

bool AHumanController::Server_Set_Name_Validate(FName Name)
{
	return true;
}

void AHumanController::InitializeHUD_Implementation()
{
}

void AHumanController::InputYaw(float Value) 
{
	if(GameInstance)
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
}
void AHumanController::InputPitch(float Value)
{
	if(GameInstance)
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

void AHumanController::InputBurst()
{
	if(SubjectZero)
	{
		SubjectZero->SetBurst(true);
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
void AHumanController::InputSecondaryFirePress()
{
	if(SubjectZero)
	{
		SubjectZero->SetSecondaryFire(true);
	}
	else if(Spectator)
	{
		Spectator->SetSecondaryFire(true);
	}
}
void AHumanController::InputSecondaryFireRelease()
{
	if(SubjectZero)
	{
		SubjectZero->SetSecondaryFire(false);
	}
	else if(Spectator)
	{
		Spectator->SetSecondaryFire(false);
	}
}
void AHumanController::InputSlot0()
{
	if (SubjectZero)
	{
		SubjectZero->Slot0();
	}
	else if (Spectator)
	{
		Spectator->Slot0();
	}
}
void AHumanController::InputSlot1()
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
void AHumanController::InputSlot2()
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

void AHumanController::InputInteractPress()
{
	if(SubjectZero)
	{
		SubjectZero->SetInteract(true);
	}
	else if(Spectator)
	{
		Spectator->SetInteract(true);
	}
}

void AHumanController::InputScoreboardPress()
{
	if(PlayerScoreboard)
	{
		PlayerScoreboard->SetVisibility(ESlateVisibility::Visible);
		if(UScoreboardWidget * Scoreboard = Cast<UScoreboardWidget>(PlayerScoreboard))
		{
			Scoreboard->Update();
		}
	}
}

void AHumanController::InputScoreboardRelease()
{
	if (PlayerScoreboard) 
	{
		PlayerScoreboard->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AHumanController::InputReload()
{
	if(SubjectZero)
	{
		SubjectZero->Reload();
	}
}

void AHumanController::InputQuickOpenInventory()
{
	bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());
	ToggleInventory(true);
}

void AHumanController::InputQuickCloseInventory()
{
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
	ToggleInventory(false);
}

FName AHumanController::GetPlayerName() const { return PlayerName; }