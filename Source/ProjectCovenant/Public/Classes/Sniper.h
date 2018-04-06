// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/ProjectileWeapon.h"
#include "Sniper.generated.h"

/**
*
*/
UCLASS()
class PROJECTCOVENANT_API ASniper : public AProjectileWeapon
{
	GENERATED_BODY()

public:
	ASniper();

	//(X=-11.613207,Y=-9.664268,Z=-143.776260)
	FVector AimDownSightsLocation = FVector(-11.613207f, -9.664268f, -143.776260f);
	//(Pitch=3.000000,Yaw=-11.799988,Roll=0.000000)
	FRotator AimDownSightsRotation = FRotator(3.000000f, -11.799988f, 0.000000f);

	//(X=-3.708951,Y=2.986693,Z=-146.510452)
	FVector HipFireLocation = FVector(-3.708951f, 2.986693f, -146.510452f);
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

	virtual void AimDownSights(bool IsAimDownSights) override;

	virtual FVector GetAimDownSightsLocation() override;

	virtual FRotator GetAimDownSightsRotation() override;

	virtual FVector GetHipFireLocation() override;

	virtual FRotator GetHipFireRotation() override;
};
