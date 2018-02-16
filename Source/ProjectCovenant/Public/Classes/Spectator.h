// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "Spectator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ASpectator : public ASpectatorPawn
{
	GENERATED_BODY()

	public:
		ASpectator();
	
	protected:
		virtual void SetupPlayerInputComponent(class UInputComponent* Input) override;

private:
	virtual void Spawn();
	
};
