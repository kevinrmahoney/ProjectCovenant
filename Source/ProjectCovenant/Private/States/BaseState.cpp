// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "UnrealNetwork.h"
#include "BaseState.h"

ABaseState::ABaseState()
{
	SetActorTickEnabled(true);
}

void ABaseState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseState, TimeLeft);
}

void ABaseState::BeginPlay()
{
	Logger::Log("ABaseState");
	TimeLeft = UGameplayStatics::GetRealTimeSeconds(GetWorld());
}

void ABaseState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ABaseState::GetTimeLeft()
{
	return TimeLeft;
}

void ABaseState::GameOver_Implementation()
{
	GameOverScreen();
}