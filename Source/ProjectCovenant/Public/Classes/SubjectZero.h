// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Item.h"
#include "SubjectZero.generated.h"

class AWeapon;
class UInventory;
class UItem;
struct FItemSerialized;
class IInteractableObject;

USTRUCT(BlueprintType)
struct FSkin : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh * ThirdPersonSkin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh * FirstPersonSkin;
};

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
	float DefaultFieldOfView = 90.f;
	float AimDownSightsFieldOfView = 70.f;

private:
	UPROPERTY()
	UInteractor * Interactor;

	UPROPERTY()
	AWeapon * Weapon;

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_Equip)
	FName EquippedItemID = TEXT("-1");

	UPROPERTY(Replicated)
	bool JetpackUsed = false;

	FVector Velocity = FVector::ZeroVector;

	UPROPERTY()
	UInventory * Inventory;

	bool Grounded = false;
	bool IsInPod = false;

	float Time;
	float TimeSinceJetpack = 0.f;
	float TimeSinceTookDamage = 0.f;
	float ShieldRechargeTime = 5.f;
	float ShieldRechargeRate = 20.f;
	float JetpackDisableTime = 5.f;

	UPROPERTY(Replicated)
	float Health = 100.f;

	UPROPERTY(Replicated)
	float Armor = 100.f;

	UPROPERTY(Replicated)
	float Shield = 100.f;

	UPROPERTY(Replicated)
	float Fuel = 10000.f;

	UPROPERTY(Replicated)
	bool Crouching = false;

	UPROPERTY(Replicated)
	bool IsTriggerPulled = false;

	UPROPERTY(Replicated)
	bool AimDownSights = false;

	UPROPERTY(Replicated)
	float Pitch = 0.f;

	UPROPERTY(Replicated)
	bool IsJetpackDisabled = false;

	FRotator HipfireRotation = FRotator(3.500000f, -19.000000f, 2.876152f);
	FVector HipfireLocation = FVector(-15.419446f, 10.841988f, -152.856400f);

	// Jetpack and air control
	float NormalGravityScale = 1.f;
	float NormalAirControl = 0.5f;
	float AirResistanceConstant = 0.00004f;
	float JetpackSpeedScale = 1.f;
	float JetpackAcceleration = 1200.f;
	float JetpackBurstImpulse = 1500.f;
	float JetpackFuelUsageRate = 75.f;
	float JetpackFuelGainRate = 200.f;

	// Grounded speeds depending on stance
	float JumpSpeed = 600.f;
	float StandingHeight = 88.f;
	float CrouchingHeight = 66.f;
	float GroundAcceleration = 5000.f;
	float StandingSprintSpeed = 600.f;
	float StandingRunSpeed = 400.f;
	float CrouchingSprintSpeed = 300.f;
	float CrouchingRunSpeed = 200.f;
	float AimDownSightsSpeed = 200.f;

	// Player counters for vitals and resources
	float MaxHealth = 100.f;
	float MaxArmor = 100.f;
	float MaxShield = 100.f;
	float MaxFuel = 10000.f;

	// Variables for movement and actions
	bool Left = false;
	bool Right = false;
	bool Forward = false;
	bool Backward = false;
	bool Burst = false;

public:
	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent * FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;
	
private:
	UFUNCTION()
	void Update();

	UFUNCTION()
	void Move();

	UFUNCTION()
	void Jetpack(FVector Input);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerJetpack(FVector Input);

	UFUNCTION()
	void ApplyAirResistance();

	UFUNCTION()
	void Equip(int Slot);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Equip(FName ItemID);

	UFUNCTION()
	void OnRep_Equip();

	void CalculateMovement();

protected:
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	virtual void Restart() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool ReceiveDamage(float Damage, bool SelfDamage = false);

	virtual void Destroyed() override;

	bool ReceiveDamageOverTime(float DamageAmount, bool Overlapped);
  
	void IncreaseHealth(float amount);

	void IncreaseArmor(float amount);

	void IncreaseFuel(float amount);

	void DamageBoost(float Multiplier, float Duration);

	void SetSkin(USkeletalMesh * TPMesh, USkeletalMesh * FPMesh);
  
	void Kill();

	UFUNCTION()
	void SetYaw(float Set);

	UFUNCTION()
	void SetPitch(float Set);

	UFUNCTION()
	void StartCrouching();
	UFUNCTION()
	void StopCrouching();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetCrouch(bool Set);

	UFUNCTION()
	void StartSprinting();
	UFUNCTION()
	void StopSprinting();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetSprint(bool Set);

	UFUNCTION()
	void StartJump();
	UFUNCTION()
	void StopJump();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetJump(bool Set);

	UFUNCTION()
	void SetBurst();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetBurst();

	UFUNCTION()
	void StartMovingLeft();
	UFUNCTION()
	void StopMovingLeft();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetMoveLeft(bool Set);

	UFUNCTION()
	void StartMovingRight();
	UFUNCTION()
	void StopMovingRight();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetMoveRight(bool Set);

	UFUNCTION()
	void StartMovingForward();
	UFUNCTION()
	void StopMovingForward();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetMoveForward(bool Set);

	UFUNCTION()
	void StartMovingBackward();
	UFUNCTION()
	void StopMovingBackward();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetMoveBackward(bool Set);

	UFUNCTION()
	void StartFiring();
	UFUNCTION()
	void StopFiring();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetFire(bool Set);

	UFUNCTION()
	void StartSecondaryFiring();
	UFUNCTION()
	void StopSecondaryFiring();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetSecondaryFire(bool Set);

	UFUNCTION()
	void StartInteracting();
	UFUNCTION()
	void StopInteracting();
	UFUNCTION()
	void InteractWith(TScriptInterface<IInteractableObject> Interactable);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerInteractWith(UObject * Interactable);
	
	void EquipFirstWeapon();
	void EquipSecondWeapon();
	void EquipThirdWeapon();

	UFUNCTION(BlueprintCallable)
	void DropItem(int Index);
	UFUNCTION(BlueprintCallable)
	void Drop(UItem * Item);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerDrop(const FItemSerialized & ItemSerialized);

	UFUNCTION(BlueprintCallable)
	void AtomizeItem(int Index);
	UFUNCTION(BlueprintCallable)
	void Atomize(UItem * Item);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerAtomize(const FItemSerialized & ItemSerialized);

	UFUNCTION()
	void Reload();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerReload();
  
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
	AWeapon* GetWeapon() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetPitch() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool GetIsInPod() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	UInventory * GetInventory() const;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRequestStartingInventory();

	UFUNCTION()
	void RequestStartingInventory();

	UFUNCTION(Client, Reliable)
	void ClientAddItemToInventory(const FItemSerialized & ItemSerialized);

	UFUNCTION()
	void AddItemToInventory(UItem * Item);

	UFUNCTION()
	void RequestPreferredSkin();
	UFUNCTION(Client, Reliable)
	void ClientRequestPreferredSkin();

	UFUNCTION()
	void SetPreferredSkin(USkeletalMesh * ThirdPersonSkin, USkeletalMesh * FirstPersonSkin);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetPreferredSkin(USkeletalMesh * ThirdPersonSkin, USkeletalMesh * FirstPersonSkin);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetPreferredSkin(USkeletalMesh * ThirdPersonSkin, USkeletalMesh * FirstPersonSkin);

	UFUNCTION()
	void SetIsInPod(bool NewIsInPod);

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