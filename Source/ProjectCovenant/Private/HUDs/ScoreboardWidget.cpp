// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "ScoreboardWidget.h"

UScoreboardWidget::UScoreboardWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UScoreboardWidget::Update()
{
	if(ABaseState * State = Cast<ABaseState>(GetWorld()->GetGameState()))
	{
		Logger::Chat("HELLO");
		UpdateScoreboard(State);
	}
}