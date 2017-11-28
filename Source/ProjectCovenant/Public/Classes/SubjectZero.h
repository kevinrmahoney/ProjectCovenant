// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SubjectZero.generated.h"

UCLASS()
class PROJECTCOVENANT_API ASubjectZero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASubjectZero();

private:

	bool LogsOn = true;
	FVector Velocity;
	FVector Movement;
	bool Jumping = false;
	bool Sprinting = false;
	bool JetpackActive = false;
	bool Grounded = false;

	float Time;

	float Health = 80.f;
	float Armor = 90.f;
	float Shield = 50.f;
	float Fuel = 1000.f;

	const float NormalAirControl = 0.3f;
	const float JumpSpeed = 500.f;
	const float JetpackSpeedScale = 1.f;
	const float MaxGroundSpeed = 400.f;
	const float JetpackAcceleration = 130000.f;
	const float GroundAcceleration = 1000.f;
	const float AirResistanceConstant = 0.003f;
	const float FuelUsage = 1.f;
	const float MaxHealth = 100.f;
	const float MaxArmor = 100.f;
	const float MaxShield = 100.f;
	const float MaxFuel = 1000.f;

private:
	void Move();
	void DepleteJetpack();
	void JetpackBurst();
	void ApplyAirResistance();

	//Input functions
	void InputForwardPress();
	void InputForwardRelease();
	void InputBackwardPress();
	void InputBackwardRelease();
	void InputLeftPress();
	void InputLeftRelease();
	void InputRightPress();
	void InputRightRelease();
	void InputJumpPress();
	void InputJumpRelease();
	void InputSprintPress();
	void InputSprintRelease();

	UFUNCTION()
	void Log(FString msg);

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* Input) override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetSpeed() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetVerticalSpeed() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetMaxHealth();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetHealth();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetMaxArmor() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetArmor() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetMaxShield() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetShield() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetMaxFuel() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetFuel() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsJetpackActive() const;
};