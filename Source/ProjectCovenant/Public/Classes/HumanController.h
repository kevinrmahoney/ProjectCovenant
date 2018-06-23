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

	UFUNCTION(BlueprintCallable)
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

	UPROPERTY(BlueprintReadWrite)
	UUserWidget * PlayerHUD;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget * PlayerScoreboard;

	UFUNCTION(Exec)
	void God(FString Set);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_God(const FString & Set);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHotbar();

	UFUNCTION(BlueprintImplementableEvent)
	void DrawZoomCrosshair(bool IsScoped);

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
	void InputBurst();
	void InputSprintPress();
	void InputSprintRelease();
	void InputCrouchPress();
	void InputCrouchRelease();
	void InputShootPress();
	void InputShootRelease();
	void InputSecondaryFirePress();
	void InputSecondaryFireRelease();
	void InputSlot0();
	void InputSlot1();
	void InputSlot2();
	void InputSlot3();
	void InputSlot4();
	void InputSlot5();
	void InputSlot6();
	void InputSlot7();
	void InputSlot8();
	void InputSlot9();
	void InputUsePress();
	void InputScoreboardPress();
	void InputScoreboardRelease();
	void InputReload();
};