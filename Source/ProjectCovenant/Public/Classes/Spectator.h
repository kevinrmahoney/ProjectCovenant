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

	void LookRight(float Set);
	void LookUp(float Set);
	void Crouch(bool Set);
	void Sprint(bool Set);
	void Jump(bool Set);
	void MoveLeft(bool Set);
	void MoveRight(bool Set);
	void MoveForward(bool Set);
	void MoveBackward(bool Set);
	void Fire(bool Set);
	void SecondaryFire(bool Set);
	void Use(bool Set);
	void Slot0();
	void Slot1();
	void Slot2();
	void Slot3();

private:
	FVector Movement;
	bool Sprinting;
	
};
