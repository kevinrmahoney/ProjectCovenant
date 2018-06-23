// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/HitscanWeapon.h"
#include "Shotgun.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API AShotgun : public AHitscanWeapon
{
	GENERATED_BODY()

public: 
	AShotgun();

	//(X=-6.900000,Y=-7.933466,Z=-151.000000)
	FVector AimDownSightsLocation = FVector(-6.900000f,-7.933466f,-151.000000f);
	//(Pitch=3.300000,Yaw=-11.800000,Roll=0.000008)
	FRotator AimDownSightsRotation = FRotator(3.300000f,-11.800000f,0.000000f);

	//(X=1.575968,Y=11.798502,Z=-153.145187)
	FVector HipFireLocation = FVector(1.575968f, 11.798502f, -153.145187f);
	//(Pitch=3.000000,Yaw=-12.000000,Roll=0.000000)
	FRotator HipFireRotation = FRotator(3.000000f, -12.000000f, 0.000000f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Update(float DeltaTime) override;

	virtual void ConstructShotVectors() override;

	void Fire() override;

private:
	void Shoot() override;

	void DealDamage(ASubjectZero * Victim, float TotalDamage) override;

	float MaxConeAngle = 1000.f;

	//maybe change to FRotator
	float RollCount = 8.f;

	float CircleCount = 4.f;

	virtual FVector GetAimDownSightsLocation() override;

	virtual FRotator GetAimDownSightsRotation() override;

	virtual FVector GetHipFireLocation() override;

	virtual FRotator GetHipFireRotation() override;
};
