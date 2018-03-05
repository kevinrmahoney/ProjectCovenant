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
	float Damage = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Range = 20000.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Cooldown = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Falloff = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Ammo = 100.f;

	bool Trigger = false;
	float TimeSinceLastShot = Cooldown;

public:
	UPROPERTY()
	ASubjectZero * Shooter = nullptr;

	//(X = -4.133434, Y = -0.131399, Z = -150.845200)
	FVector HipfireLocation = FVector(-4.133434f, -0.131399f, -150.845200f);
	//(Pitch = 2.812467, Yaw = -19.000458, Roll = 0.000000)
	FRotator HipfireRotation = FRotator(2.812467f, -19.000458f, 0.000000f);

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

	virtual void DrawLaser(FVector * Begin, FVector * End, float Duration);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTrigger(bool T);

	void SetShooter(ASubjectZero * NewShooter);

	virtual FVector GetAimDownSightsLocation();

	virtual FRotator GetAimDownSightsRotation();
};