// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "HitscanWeapon.generated.h"

class ASubjectZero;

UCLASS()
class PROJECTCOVENANT_API AHitscanWeapon : public AWeapon
{
	GENERATED_BODY()
	
// Sets default values for this actor's properties
public:
	AHitscanWeapon();

	//(X=-6.456540,Y=-7.700000,Z=-148.210724)
	FVector AimDownSightsLocation = FVector(-6.456540f,-7.700000f,-148.210724f);
	//(Pitch=2.500000,Yaw=-11.700012,Roll=0.000000)
	FRotator AimDownSightsRotation = FRotator(2.500000f,-11.700012f,0.000000f);

	//(X=1.575968,Y=11.798502,Z=-153.145187)
	FVector HipFireLocation = FVector(1.575968f, 11.798502f, -153.145187f);
	//(Pitch=3.000000,Yaw=-12.000000,Roll=0.000000)
	FRotator HipFireRotation = FRotator(3.000000f, -12.000000f, 0.000000f);

protected:
	// How much heat is added to HeatAllowable when Heat
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OverHeatPenalty;

	// Threshold for heat. If passed, weapon must be completely cooled down before use
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeatThreshold = 100.f;

	// If the weapon is cooling down after hitting the heat threshold
	UPROPERTY(BlueprintReadOnly)
	bool IsCoolingDown = false;

	// Between 0 and OptimalRange, this weapon does 100% of Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OptimalRange;

	// The maximum distance that a player can be hit by this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaximumRange;

	// How much damage is reduced at max range (Damage * FallOff)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FallOff = 1.f;

	// How much heat is generated for each shot
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeatGeneratedPerShot;

	// Current heat level of the weapon
	UPROPERTY(BlueprintReadOnly)
	float Heat = 0.f;

	// Rate of cool down for weapon (per second)
	UPROPERTY()
	float CooldownRate = 50.f;

	// Seconds after a shot is ready before the gun starts passively cooling down
	UPROPERTY()
	float CooldownPause = 0.5f;

	// Timer for cooldown pause
	UPROPERTY()
	float CooldownPauseTimer = 0.f;

private:
	virtual void BeginCooldown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void DealDamage(ASubjectZero * Victim, float TotalDamage) override;

	virtual void DrawDebugVisuals() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ConstructShotVectors() override;

	virtual void Update(float DeltaTime) override;

	virtual bool CanFire() override;

	virtual void Fire() override;

	virtual void BeginReload() override;

	virtual void SetItem(UItem * NewItem);

	virtual FVector GetAimDownSightsLocation();

	virtual FRotator GetAimDownSightsRotation();

	virtual FVector GetHipFireLocation();

	virtual FRotator GetHipFireRotation();

	void Destroyed() override;
};