// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Deathmatch.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ADeathmatch : public AGameMode
{
	GENERATED_BODY()
	public:
		ADeathmatch();
	
	private:
		void PostLogin(APlayerController * NewPlayer);
};
