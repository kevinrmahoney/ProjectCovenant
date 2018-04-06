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

AHumanController::AHumanController()
{

}

void AHumanController::BeginPlay()
{
	Super::BeginPlay();
	Logger::Log("Begin: " + GetName());
	if(IsLocalController())
	{
		InitializeHUD();
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
		InputComponent->BindAction("Slot 0", IE_Pressed, this, &AHumanController::InputSlot0);
		InputComponent->BindAction("Slot 1", IE_Pressed, this, &AHumanController::InputSlot1);
		InputComponent->BindAction("Slot 2", IE_Pressed, this, &AHumanController::InputSlot2);
		InputComponent->BindAction("Slot 3", IE_Pressed, this, &AHumanController::InputSlot3);
		InputComponent->BindAction("Slot 4", IE_Pressed, this, &AHumanController::InputSlot4);
		InputComponent->BindAction("Slot 5", IE_Pressed, this, &AHumanController::InputSlot5);
		InputComponent->BindAction("Slot 6", IE_Pressed, this, &AHumanController::InputSlot6);
		InputComponent->BindAction("Slot 7", IE_Pressed, this, &AHumanController::InputSlot7);
		InputComponent->BindAction("Slot 8", IE_Pressed, this, &AHumanController::InputSlot8);
		InputComponent->BindAction("Slot 9", IE_Pressed, this, &AHumanController::InputSlot9);
		InputComponent->BindAction("Use", IE_Pressed, this, &AHumanController::InputUsePress);
		InputComponent->BindAction("Scoreboard", IE_Pressed, this, &AHumanController::InputScoreboardPress);
		InputComponent->BindAction("Scoreboard", IE_Released, this, &AHumanController::InputScoreboardRelease);
	}
}

void AHumanController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME(AHumanController, Health)
}

void AHumanController::God(FString Set = "")
{
	if(Role == ROLE_AutonomousProxy)
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

void AHumanController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

	if(ASubjectZero * NewSubjectZero = Cast<ASubjectZero>(AcknowledgedPawn))
	{
		Logger::Log("Spawning as SubjectZero");
		SubjectZero = NewSubjectZero;
		Spectator = nullptr;
		UpdateHotbar();
	} 
	else if(ASpectator * NewSpectator = Cast<ASpectator>(AcknowledgedPawn))
	{
		Logger::Log("Spawning as Spectator");
		Spectator = NewSpectator;
		SubjectZero = nullptr;
	}
}

void AHumanController::UnPossess()
{
	Super::UnPossess();
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

void AHumanController::InitializeHUD()
{
	Logger::Log("Initializing HUD");

	Logger::Log("Initializing Base HUD");
	if(HUD)
	{
		PlayerHUD = CreateWidget<UUserWidget>(this, HUD);
		if(PlayerHUD)
		{
			PlayerHUD->AddToViewport();
		}
	}

	Logger::Log("Initializing Scoreboard");
	if(Scoreboard)
	{
		PlayerScoreboard = CreateWidget<UUserWidget>(this, Scoreboard);
		if(PlayerScoreboard)
		{
			PlayerScoreboard->AddToViewport();
			PlayerScoreboard->SetVisibility(ESlateVisibility::Hidden);
		}
	}
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
		SubjectZero->Slot9();
	}
	else if (Spectator)
	{
		Spectator->Slot9();
	}
}
void AHumanController::InputSlot1()
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
void AHumanController::InputSlot2()
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
void AHumanController::InputSlot3()
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

void AHumanController::InputSlot4()
{
	if(SubjectZero)
	{
		SubjectZero->Slot3();
	}
	else if(Spectator)
	{
		Spectator->Slot3();
	}
}
void AHumanController::InputSlot5()
{
	if (SubjectZero)
	{
		SubjectZero->Slot4();
	}
	else if (Spectator)
	{
		Spectator->Slot4();
	}
}
void AHumanController::InputSlot6()
{
	if (SubjectZero)
	{
		SubjectZero->Slot5();
	}
	else if (Spectator)
	{
		Spectator->Slot5();
	}
}
void AHumanController::InputSlot7()
{
	if (SubjectZero)
	{
		SubjectZero->Slot6();
	}
	else if (Spectator)
	{
		Spectator->Slot6();
	}
}
void AHumanController::InputSlot8()
{
	if (SubjectZero)
	{
		SubjectZero->Slot7();
	}
	else if (Spectator)
	{
		Spectator->Slot7();
	}
}
void AHumanController::InputSlot9()
{
	if (SubjectZero)
	{
		SubjectZero->Slot8();
	}
	else if (Spectator)
	{
		Spectator->Slot8();
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

void AHumanController::InputScoreboardPress()
{
	PlayerScoreboard->SetVisibility(ESlateVisibility::Visible);
	if(UScoreboardWidget * ScoreboardWidget = Cast<UScoreboardWidget>(PlayerScoreboard))
	{
		ScoreboardWidget->Update();
	}
}

void AHumanController::InputScoreboardRelease()
{
	if (PlayerScoreboard) 
	{
		PlayerScoreboard->SetVisibility(ESlateVisibility::Hidden);
	}
}

FName AHumanController::GetPlayerName() const { return PlayerName; }