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

	void OnPossess(APawn* aPawn) override;

	void OnUnPossess() override;

	void SetPawn(APawn * NewPawn) override;

	UPROPERTY(BlueprintReadOnly)
	ASubjectZero * SubjectZero;

	UPROPERTY(BlueprintReadOnly)
	ASpectator * Spectator;

	UFUNCTION(BlueprintCallable)
	ASubjectZero * GetSubjectZero();

	UFUNCTION(BlueprintCallable)
	FName GetPlayerName() const;

	UPROPERTY()
	FName PlayerName = "Subject Zero";

	bool GodMode = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD")
	TSubclassOf<class UUserWidget> SpectatorHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> SubjectZeroHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> ScoreboardWidget;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget * PlayerHUD;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget * PlayerScoreboard;

	UFUNCTION(Exec)
	void God(FString Set);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_God(const FString & Set);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHUD();

	UFUNCTION(BlueprintImplementableEvent)
	void DrawZoomCrosshair(bool IsScoped);

	UFUNCTION(BlueprintImplementableEvent)
	void ToggleInventory(bool Toggle);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitializeHUD();

protected:
	void BeginPlay();
	void SetupInputComponent() override;

	UFUNCTION(BlueprintImplementableEvent)
	void ToggleEscapeMenu();

private:
	UPROPERTY()
	UProjectCovenantInstance * GameInstance;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Set_Name(const FName NewName);

	UPROPERTY()
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
	void InputInteractPress();
	void InputScoreboardPress();
	void InputScoreboardRelease();
	void InputReload();
	void InputQuickOpenInventory();
	void InputQuickCloseInventory();
	void InputEscape();
};