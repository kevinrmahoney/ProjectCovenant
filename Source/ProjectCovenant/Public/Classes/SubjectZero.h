// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SubjectZero.generated.h"

class UProjectCovenantInstance;

class AHitscanWeapon;
class ARailgun;

UCLASS()
class PROJECTCOVENANT_API ASubjectZero : public ACharacter
{
	GENERATED_BODY()

public:
	ASubjectZero(const FObjectInitializer& ObjectInitializer);

private:

	UPROPERTY()
	UProjectCovenantInstance * GameInstance;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHitscanWeapon> HitscanWeaponBlueprint;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ARailgun> RailgunBlueprint;

	UPROPERTY()
	AHitscanWeapon * Weapon;

	FVector Velocity;
	FVector Movement;
	bool Jumping = false;
	bool Sprinting = false;
	bool JetpackActive = false;

	bool Grounded = false;

	float Time;       

	UPROPERTY(Replicated)
	float Health = 50.f;

	UPROPERTY(Replicated)
	float Armor = 100.f;

	UPROPERTY(Replicated)
	float Shield = 100.f;

	UPROPERTY(Replicated)
	float Fuel = 1000.f;

	UPROPERTY(Replicated)
	int Kills = 0;

	UPROPERTY(Replicated)
	int DamageDealt = 0;

	UPROPERTY(Replicated)
	FName PlayerName = "Subject Zero";

	UPROPERTY(Replicated)
	bool Crouching = false;

	UPROPERTY(Replicated)
	bool IsTriggerPulled = false;

	// constants
	float NormalAirControl = 0.3f;
	float JumpSpeed = 500.f;
	float JetpackSpeedScale = 1.f;
	float StandingSprintSpeed = 600.f;
	float StandingRunSpeed = 400.f;
	float CrouchingSprintSpeed = 300.f;
	float CrouchingRunSpeed = 200.f;
	float JetpackAcceleration = 120000.f;
	float GroundAcceleration = 1000.f;
	float AirResistanceConstant = 0.008f;
	float FuelUsage = 1.f;
	float MaxHealth = 100.f;
	float MaxArmor = 100.f;
	float MaxShield = 100.f;
	float MaxFuel = 1000.f;
	float StandingHeight = 75.f;
	float CrouchingHeight = 15.f;

public:
	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent * FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;

private:
	void Move(FVector Client_Movement, bool Client_Jumping, bool Client_Sprinting, bool Client_Crouching, bool Client_JetpackActive, bool Client_Shooting, float Client_Pitch);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Move(FVector Client_Movement, bool Client_Jumping, bool Client_Sprinting, bool Client_Crouching, bool Client_JetpackActive, bool Client_Shooting, float Client_Pitch);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Set_Name(const FName NewName);
  
	void DepleteJetpack();

	void JetpackBurst();

	void ApplyAirResistance();

	//Input functions
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
	void InputPrimaryWeaponRelease();
	void InputSecondaryWeaponPress();
	void InputSecondaryWeaponRelease();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* Input) override;

public:
	virtual void Tick(float DeltaTime) override;

	bool ReceiveDamage(float Damage);

	bool ReceiveDamageOverTime(float DamageAmount, bool Overlapped);

	void AddDamageDealt(float DamageDealt);

	void AddKill();

	void IncreaseHealth(float amount);
  
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
	int GetKills() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetDamage() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FName GetPlayerName() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsJetpackActive() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsSprinting() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsCrouching() const;

	UFUNCTION(Exec, BlueprintPure, BlueprintCallable)
	bool Join(FString IPAddress);

	UFUNCTION(Exec, BlueprintPure, BlueprintCallable)
	bool Host();

	UFUNCTION(Exec, BlueprintPure, BlueprintCallable)
	bool Map(FString Map);
};