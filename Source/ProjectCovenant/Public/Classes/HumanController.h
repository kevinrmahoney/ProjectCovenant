// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HumanController.generated.h"

class UProjectCovenantInstance;
class ASubjectZero;
class ASpectator;

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API AHumanController : public APlayerController
{
	GENERATED_BODY()

public:
	AHumanController();
	void Tick(float DeltaTime);

	void Possess(APawn* aPawn) override;

	void UnPossess() override;

	ASubjectZero * SubjectZero;

	ASpectator * Spectator;

	ASubjectZero * GetSubjectZero();

	FName GetPlayerName() const;

	FName PlayerName = "Subject Zero";

protected:
	void BeginPlay();
	void SetupInputComponent() override;

private:
	UPROPERTY()
	UProjectCovenantInstance * GameInstance;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Set_Name(const FName NewName);

	APawn * PossessedPawn;

	void InputYaw(float Value);
	void InputPitch(float Value);
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
	void InputCrouchPress();
	void InputCrouchRelease();
	void InputShootPress();
	void InputShootRelease();
	void InputPrimaryWeaponPress();
	void InputSecondaryWeaponPress();
	void InputThirdaryWeaponPress();
	void InputUsePress();

};