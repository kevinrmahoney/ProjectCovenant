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
	bool JetpackActive = false;
	bool Grounded = false;
	float Time;

public:
	UPROPERTY()
	float JetpackAirControl = 1.f;

	UPROPERTY()
	float NormalAirControl = 0.f;

	UPROPERTY()
	float JetpackClimbSpeed = 25.f;

	UPROPERTY()
	float JetpackSpeed = 1000.f;

	UPROPERTY()
	float GroundSpeed = 1000.f;

	UPROPERTY()
	float MaxJetpackSpeed = 10000.f;

	UPROPERTY()
	float MaxGroundSpeed = 1000.f;

	UPROPERTY()
	float JetpackAcceleration = 1000.f;

	UPROPERTY()
	float GroundAcceleration = 1000.f;

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
	void OnJetpack(float Value);

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

};