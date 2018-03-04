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
	void Tick(float DeltaTime) override;

	void Possess(APawn* aPawn) override;

	void UnPossess() override;

	ASubjectZero * SubjectZero;

	ASpectator * Spectator;

	ASubjectZero * GetSubjectZero();

	UFUNCTION(BlueprintCallable)
	FName GetPlayerName() const;

	FName PlayerName = "Subject Zero";

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> HUD;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> Scoreboard;

	UUserWidget * PlayerHUD;

	UUserWidget * PlayerScoreboard;

protected:
	void BeginPlay();
	void SetupInputComponent() override;

private:
	UPROPERTY()
	UProjectCovenantInstance * GameInstance;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Set_Name(const FName NewName);

	APawn * PossessedPawn;

	void InitializeHUD();

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
	void InputSlot1();
	void InputSlot2();
	void InputSlot3();
	void InputUsePress();
	void InputScoreboardPress();
	void InputScoreboardRelease();
};