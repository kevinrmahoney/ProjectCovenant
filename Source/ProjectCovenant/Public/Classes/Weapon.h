// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Recoil.h"
#include "Weapon.generated.h"

class UItemWeapon;
class ASubjectZero;

UCLASS()
class PROJECTCOVENANT_API AWeapon : public AActor
{
GENERATED_BODY()

		// Sets default values for this actor's properties
public:
	AWeapon();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range = 20000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FallOff = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Ammo = 100.f;

	UPROPERTY(BlueprintReadWrite, Replicated)
	bool Trigger = false;

	float TimeSinceLastShot = 0.f;

	float Duration = 0.02f;

	TArray<FVector> ShotVectors;

	UItemWeapon * Item;

public:
	UPROPERTY()
	ASubjectZero * Shooter = nullptr;

	//(X=-6.456540,Y=-7.700000,Z=-148.210724)
	FVector AimDownSightsLocation = FVector(-6.456540f, -7.700000f, -148.210724f);
	//(Pitch=2.500000,Yaw=-11.700012,Roll=0.000000)
	FRotator AimDownSightsRotation = FRotator(2.500000f, -11.700012f, 0.000000f);

	//(X=1.575968,Y=11.798502,Z=-153.145187)
	FVector HipFireLocation = FVector(1.575968f, 11.798502f, -153.145187f);
	//(Pitch=3.000000,Yaw=-12.000000,Roll=0.000000)
	FRotator HipFireRotation = FRotator(3.000000f, -12.000000f, 0.000000f);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent * Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * GunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent * Muzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	URecoil * RecoilComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float WeaponSwitchCooldown = 0.5f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Shoot();

	virtual void DealDamage(ASubjectZero * Victim, float TotalDamage);

	virtual void DrawDebugVisuals();

	UFUNCTION(BlueprintImplementableEvent)
	void DrawVisuals();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayShootSound();

	void Destroyed() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ConstructShotVectors();

	virtual void Update();

	virtual void SetItem(UItemWeapon * NewItem);

	virtual void SetTrigger(bool T);

	virtual void SetShooter(ASubjectZero * NewShooter);

	virtual FVector GetAimDownSightsLocation() ;

	virtual FRotator GetAimDownSightsRotation();

	virtual FVector GetHipFireLocation();

	virtual FRotator GetHipFireRotation();
};
