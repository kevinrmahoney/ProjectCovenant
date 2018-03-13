// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitscanWeapon.generated.h"

class ASubjectZero;

UCLASS()
class PROJECTCOVENANT_API AHitscanWeapon : public AActor
{
	GENERATED_BODY()
	
	// Sets default values for this actor's properties
public:
	AHitscanWeapon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Damage = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Range = 20000.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Cooldown = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Falloff = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Ammo = 100.f;

	UPROPERTY(VisibleAnywhere, Replicated)
	bool Trigger = false;

	float TimeSinceLastShot = Cooldown;

	float Duration = 0.08f;

public:
	UPROPERTY()
	ASubjectZero * Shooter = nullptr;

	//(X=-6.456540,Y=-7.700000,Z=-148.210724)
	FVector AimDownSightsLocation = FVector(-6.456540f,-7.700000f,-148.210724f);
	//(Pitch=2.500000,Yaw=-11.700012,Roll=0.000000)
	FRotator AimDownSightsRotation = FRotator(2.500000f,-11.700012f,0.000000f);

	//(X=1.575968,Y=11.798502,Z=-153.145187)
	FVector HipFireLocation = FVector(1.575968f, 11.798502f, -153.145187f);
	//(Pitch=3.000000,Yaw=-12.000000,Roll=0.000000)
	FRotator HipFireRotation = FRotator(3.000000f, -12.000000f, 0.000000f);

protected:
	UPROPERTY()
	USceneComponent * Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * Mesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent * Muzzle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Shoot();

	virtual void DealDamage(ASubjectZero * Victim, float TotalDamage);

	virtual void DrawLaser();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTrigger(bool T);

	void SetShooter(ASubjectZero * NewShooter);

	virtual FVector GetAimDownSightsLocation();

	virtual FRotator GetAimDownSightsRotation();

	virtual FVector GetHipFireLocation();

	virtual FRotator GetHipFireRotation();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayShootSound();
};