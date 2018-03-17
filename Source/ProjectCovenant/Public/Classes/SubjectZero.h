// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SubjectZero.generated.h"

class AHitscanWeapon;
class ARailgun;
class AShotgun;
class UInventory;

UCLASS()
class PROJECTCOVENANT_API ASubjectZero : public ACharacter
{
	GENERATED_BODY()

public:
	ASubjectZero(const FObjectInitializer& ObjectInitializer);

	FVector Movement = FVector::ZeroVector;
	bool Jumping = false;
	bool Sprinting = false;
	bool TryJetpack = false;
	float DamageMultiplier = 1.f;
	float DamageMultiplierDuration = 0.f;

private:
	AHitscanWeapon * Weapon;

	UPROPERTY(ReplicatedUsing = OnRep_Equip)
	int Equipped = -1;

	UPROPERTY(Replicated)
	bool JetpackUsed = false;

	UPROPERTY()
	TArray<AHitscanWeapon*> Weapons;

	FVector Velocity;

	UInventory * Inventory;

	bool Grounded = false;

	float Time;
	float TimeSinceJetpack = 0.f;
	float TimeSinceTookDamage = 0.f;
	float ShieldRechargeTime = 5.f;
	float ShieldRechargeRate = 20.f;

	UPROPERTY(Replicated)
	float Health = 100.f;

	UPROPERTY(Replicated)
	float Armor = 100.f;

	UPROPERTY(Replicated)
	float Shield = 100.f;

	UPROPERTY(Replicated)
	float Fuel = 1000.f;

	UPROPERTY(Replicated)
	bool Crouching = false;

	UPROPERTY(Replicated)
	bool IsTriggerPulled = false;

	UPROPERTY(Replicated)
	bool AimDownSights = false;

	UPROPERTY(Replicated)
	float Pitch = 0.f;

	FRotator HipfireRotation = FRotator(3.500000f, -19.000000f, 2.876152f);
	FVector HipfireLocation = FVector(-15.419446f, 10.841988f, -152.856400f);

	// constants
	float NormalAirControl = 0.3f;
	float JumpSpeed = 500.f;
	float JetpackSpeedScale = 1.f;
	float StandingSprintSpeed = 600.f;
	float StandingRunSpeed = 400.f;
	float CrouchingSprintSpeed = 300.f;
	float CrouchingRunSpeed = 200.f;
	float AimDownSightsSpeed = 200.f;
	float JetpackAcceleration = 2000.f;
	float GroundAcceleration = 5000.f;
	float AirResistanceConstant = 0.00004f;
	float FuelUsage = 50.f;
	float FuelOverTime = 50.f;
	float MaxHealth = 100.f;
	float MaxArmor = 100.f;
	float MaxShield = 100.f;
	float MaxFuel = 1000.f;
	float StandingHeight = 75.f;
	float CrouchingHeight = 15.f;

	bool Left = false;
	bool Right = false;
	bool Forward = false;
	bool Backward = false;

public:
	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent * FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;

private:
	UFUNCTION()
	void Update();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerUpdate(bool NewForward, bool NewBackward, bool NewLeft, bool NewRight, bool NewJumping, bool NewSprinting, bool NewCrouching, bool NewTryJetpack, bool NewShooting, bool NewAimDownSights);

	UFUNCTION()
	void Move();

	UFUNCTION()
	void Jetpack();

	//UFUNCTION()
	//void Move(FVector Client_Movement, bool Client_Jumping, bool Client_Sprinting, bool Client_Crouching, bool Client_JetpackActive, bool Client_Shooting, float Client_Pitch, bool AimDownSights);

	//UFUNCTION(Server, Reliable, WithValidation)
	//void Server_Move(FVector Client_Movement, bool Client_Jumping, bool Client_Sprinting, bool Client_Crouching, bool Client_JetpackActive, bool Client_Shooting, float Client_Pitch, bool Client_AimDownSights);

	UFUNCTION()
	void ApplyAirResistance();

	UFUNCTION()
	void Equip(int Num);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Equip(int Num);

	UFUNCTION()
	void OnRep_Equip();

	void CalculateMovement();

protected:
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

public:
	virtual void Tick(float DeltaTime) override;

	bool ReceiveDamage(float Damage);

	virtual void Destroyed() override;

	bool ReceiveDamageOverTime(float DamageAmount, bool Overlapped);
  
	void IncreaseHealth(float amount);

	void IncreaseArmor(float amount);

	void IncreaseFuel(float amount);

	void DamageBoost(float Multiplier, float Duration);
  
	void Kill();

	UFUNCTION()
	void SetYaw(float Set);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetYaw(float Set);

	UFUNCTION()
	void SetPitch(float Set);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetPitch(float Set);

	UFUNCTION()
	void SetCrouch(bool Set);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetCrouch(bool Set);

	UFUNCTION()
	void SetSprint(bool Set);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetSprint(bool Set);

	UFUNCTION()
	void SetJump(bool Set);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetJump(bool Set);

	UFUNCTION()
	void SetMoveLeft(bool Set);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetMoveLeft(bool Set);

	UFUNCTION()
	void SetMoveRight(bool Set);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetMoveRight(bool Set);

	UFUNCTION()
	void SetMoveForward(bool Set);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetMoveForward(bool Set);

	UFUNCTION()
	void SetMoveBackward(bool Set);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetMoveBackward(bool Set);

	UFUNCTION()
	void SetFire(bool Set);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetFire(bool Set);

	UFUNCTION()
	void SetSecondaryFire(bool Set);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetSecondaryFire(bool Set);

	UFUNCTION()
	void SetUse(bool Set);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetUse(bool Set);

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
	float GetDamageMultiplier() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FName GetPlayerName() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetPitch() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsJetpackUsed() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsJetpackActive() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsSprinting() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsCrouching() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsAimingDownSights() const;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayJetpackSound();
};