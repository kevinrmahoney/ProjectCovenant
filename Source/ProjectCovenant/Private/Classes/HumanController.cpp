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
}

void AHumanController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(InputComponent)
	{
		InputComponent->BindAction("Scoreboard", IE_Pressed, this, &AHumanController::InputScoreboardPress);
		InputComponent->BindAction("Scoreboard", IE_Released, this, &AHumanController::InputScoreboardRelease);
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

void AHumanController::UnPossess()
{
	Super::UnPossess();
}

void AHumanController::SetPawn(APawn * NewPawn)
{
	Super::SetPawn(NewPawn);

	if(IsLocalController())
	{
		SubjectZero = Cast<ASubjectZero>(NewPawn);
		if(SubjectZero) SubjectZero->SetupPlayerInputComponent(InputComponent);
		Spectator = Cast<ASpectator>(NewPawn);
		if(Spectator) Spectator->SetupPlayerInputComponent(InputComponent);
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