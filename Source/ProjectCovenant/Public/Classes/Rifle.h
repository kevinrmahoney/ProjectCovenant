// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/ProjectileWeapon.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ARifle : public AProjectileWeapon
{
	GENERATED_BODY()
	
public:
	ARifle();

	//(X=-11.357482,Y=-8.996102,Z=-145.574875)
	FVector AimDownSightsLocation = FVector(-11.357482f, -8.996102f, -145.574875f);
	//(Pitch=3.000000,Yaw=-11.800000,Roll=0.000000)
	FRotator AimDownSightsRotation = FRotator(3.000000f, -11.800000f, 0.000000f);

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

	virtual void Update() override;

	virtual void ConstructShotVectors() override;

protected:
	void Shoot() override;

	void DealDamage(ASubjectZero * Victim, float TotalDamage) override;

	virtual FVector GetAimDownSightsLocation() override;

	virtual FRotator GetAimDownSightsRotation() override;

	virtual FVector GetHipFireLocation() override;

	virtual FRotator GetHipFireRotation() override;	
	
};
