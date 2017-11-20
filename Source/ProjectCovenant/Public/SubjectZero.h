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
	UFUNCTION()
	void MoveForwardBackward(float Val);

	UFUNCTION()
	void MoveLeftRight(float Val);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Player input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
