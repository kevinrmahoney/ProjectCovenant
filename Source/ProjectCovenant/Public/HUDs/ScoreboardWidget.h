// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseState.h"
#include "ScoreboardWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API UScoreboardWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UScoreboardWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateScoreboard(ABaseState * State);

	void Update();
};
