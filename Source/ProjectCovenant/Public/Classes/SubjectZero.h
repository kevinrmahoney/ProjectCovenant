// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SubjectZero.generated.h"

class AHitscanWeapon;
class ARailgun;

UCLASS()
class PROJECTCOVENANT_API ASubjectZero : public ACharacter
{
	GENERATED_BODY()

public:
	ASubjectZero(const FObjectInitializer& ObjectInitializer);

	FVector Movement;
	bool Jumping = false;
	bool Sprinting = false;
	bool JetpackActive = false;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHitscanWeapon> HitscanWeaponBlueprint;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ARailgun> RailgunBlueprint;

	UPROPERTY()
	AHitscanWeapon * Weapon;

	FVector Velocity;

	bool Grounded = false;

	float Time;    
	float TimeSinceJetpack = 0.f;

	UPROPERTY(Replicated)
	float Health = 100.f;

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
	float GroundAcceleration = 5000.f;
	float AirResistanceConstant = 0.008f;
	float FuelUsage = 100.f;
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

	void JetpackBurst();

	void ApplyAirResistance();

	void Equip(int Num);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Equip(int Num);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	bool ReceiveDamage(float Damage);

	void AddDamageDealt(float DamageDealt);

	void AddKill();

	void Kill();

	void SetYaw(float Set);
	void SetPitch(float Set);
	void SetCrouch(bool Set);
	void SetSprint(bool Set);
	void SetJump(bool Set);
	void SetMoveLeft(bool Set);
	void SetMoveRight(bool Set);
	void SetMoveForward(bool Set);
	void SetMoveBackward(bool Set);
	void SetFire(bool Set);
	void SetSecondaryFire(bool Set);
	void SetUse(bool Set);
	void Slot0();
	void Slot1();
	void Slot2();
	void Slot3();
  
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
	FName GetPlayerName() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsJetpackActive() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsSprinting() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsCrouching() const;


};