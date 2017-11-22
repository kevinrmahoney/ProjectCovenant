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
	UPROPERTY()
	bool JetpackActive = false;

	UPROPERTY()
	bool Grounded = false;

	UPROPERTY()
	float Time;

	UPROPERTY()
	float MaxHealth = 100.f;

	UPROPERTY()
	float Health = 80.f;

	UPROPERTY()
	float MaxArmor = 100.f;

	UPROPERTY()
	float Armor = 90.f;

	UPROPERTY()
	float MaxShield = 100.f;

	UPROPERTY()
	float Shield = 50.f;

	UPROPERTY()
	float MaxFuel = 1000.f;

	UPROPERTY()
	float Fuel = 1000.f;

	// Air control with jetpack enabled
	UPROPERTY()
	float JetpackAirControl = 1.f;

	// Air control while jetpack is disabled
	UPROPERTY()
	float NormalAirControl = 0.1f;

	// Speed with which you jump off the ground
	UPROPERTY()
	float JumpSpeed = 1000.f;

	// How fast the jetpack climbs
	UPROPERTY()
	float JetpackClimbSpeed = 25.f;

	// What percentage of jetpack speed is applied
	UPROPERTY()
	float JetpackSpeedScale = 1.f;

	// What percentage of ground speed is applied
	UPROPERTY()
	float GroundSpeedScale = 1.f;

	// Maximum obtainable speed while using the jetpack (cm/s)
	UPROPERTY()
	float MaxJetpackSpeed = 10000.f;

	// Maximum obtainable speed while on the ground (cm/s)
	UPROPERTY()
	float MaxGroundSpeed = 1000.f;

	// Acceleration while using the jetpack (cm/s/s)
	UPROPERTY()
	float JetpackAcceleration = 1000.f;

	// Acceleration while on the ground (cm/s/s)
	UPROPERTY()
	float GroundAcceleration = 1000.f;

	// Factor by which velocity changes are multiplied if decelerating
	UPROPERTY()
	float DecelerationMultiplier = 5.f;

	// Fuel usage per action per second
	UPROPERTY()
	float FuelUsage = 10.f;

	UPROPERTY()
	FVector MoveDirection;

private:
	UFUNCTION()
	void MoveForwardBackward(float Value);

	UFUNCTION()
	void MoveLeftRight(float Value);

	UFUNCTION()
	void JetpackBurst();

	UFUNCTION()
	void OnJump(float Value);

	UFUNCTION()
	void DepleteJetpack();

	UFUNCTION()
	void Log(FString msg);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Player input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetSpeed() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetVerticalSpeed() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetHealth() const;

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