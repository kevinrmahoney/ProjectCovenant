// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "BaseState.h"

ABaseState::ABaseState()
{
	SetActorTickEnabled(true);
}

void ABaseState::BeginPlay()
{
	Logger::Log("ABaseState");
}

void ABaseState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Logger::Chat("HELLO");
}

