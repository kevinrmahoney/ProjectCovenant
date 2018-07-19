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

	void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move();
	void Spawn();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Move();
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Spawn();

	// Rotation binds
	void SetYaw(float Set);
	void SetPitch(float Set);

	// Translation binds (up, down, left, right, forward, backward)
	void StartMovingUp();
	void StopMovingUp();
	void StartMovingDown();
	void StopMovingDown();
	void StartMovingForward();
	void StopMovingForward();
	void StartMovingBackward();
	void StopMovingBackward();
	void StartMovingLeft();
	void StopMovingLeft();
	void StartMovingRight();
	void StopMovingRight();

	// Respawn bind
	void Respawn();

private:
	FVector Movement = FVector::ZeroVector;
	bool Sprinting = false;

	bool Left = false;
	bool Right = false;
	bool Forward = false;
	bool Backward = false;
	bool Up = false;
	bool Down = false;
	
};
