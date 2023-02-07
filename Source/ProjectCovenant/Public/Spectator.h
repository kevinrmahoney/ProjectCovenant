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

	void Move();
	void Spawn();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Move();
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Spawn();

	void SetYaw(float Set);
	void SetPitch(float Set);
	void SetCrouch(bool Set);
	void SetSprint(bool Set);
	void SetJump(bool Set);
	void SetMoveLeft(bool Set);
	void SetMoveRight(bool Set);
	void SetMoveForward(bool Set);
	void SetMoveBackward(bool Set);
	void SetFire(bool Set);
	void SetSecondaryFire(bool Set);
	void SetInteract(bool Set);
	void Slot0();
	void Slot1();
	void Slot2();
	void Slot3();
	void Slot4();
	void Slot5();
	void Slot6();
	void Slot7();
	void Slot8();
	void Slot9();

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
