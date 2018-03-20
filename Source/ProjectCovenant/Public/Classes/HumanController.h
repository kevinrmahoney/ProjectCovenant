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

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	void Possess(APawn* aPawn) override;

	void UnPossess() override;

	UPROPERTY()
	ASubjectZero * SubjectZero;

	UPROPERTY()
	ASpectator * Spectator;

	UFUNCTION()
	ASubjectZero * GetSubjectZero();

	UFUNCTION(BlueprintCallable)
	FName GetPlayerName() const;

	UPROPERTY()
	FName PlayerName = "Subject Zero";

	bool GodMode = false;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> HUD;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> Scoreboard;

	UPROPERTY()
	UUserWidget * PlayerHUD;

	UPROPERTY()
	UUserWidget * PlayerScoreboard;

	UFUNCTION(Exec)
	void God(FString Set);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_God(const FString & Set);

protected:
	void BeginPlay();
	void SetupInputComponent() override;

private:
	UPROPERTY()
	UProjectCovenantInstance * GameInstance;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Set_Name(const FName NewName);

	UPROPERTY()
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
	void InputSecondaryFirePress();
	void InputSecondaryFireRelease();
	void InputSlot1();
	void InputSlot2();
	void InputSlot3();
	void InputSlot4();
	void InputUsePress();
	void InputScoreboardPress();
	void InputScoreboardRelease();
};