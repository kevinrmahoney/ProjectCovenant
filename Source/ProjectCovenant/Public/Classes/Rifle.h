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

	//(X=-12.526007,Y=-5.000000,Z=-148.639145)
	FVector AimDownSightsLocation = FVector(-12.526007f,-5.000000f,-148.639145f);
	//(Pitch=2.802358,Yaw=-11.900208,Roll=-0.138306)
	FRotator AimDownSightsRotation = FRotator(2.802358f,-11.900208f,-0.138306f);

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
