// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitscanWeapon.h"
#include "Railgun.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ARailgun : public AHitscanWeapon
{
	GENERATED_BODY()
	
public:
	ARailgun();

	//(X=-11.357482,Y=-8.996102,Z=-145.574875)
	FVector AimDownSightsLocation = FVector(-11.357482f,-8.996102f,-145.574875f);
	//(Pitch=3.000000,Yaw=-11.800000,Roll=0.000000)
	FRotator AimDownSightsRotation = FRotator(3.000000f,-11.800000f,0.000000f);

	//(X=1.575968,Y=11.798502,Z=-153.145187)
	FVector HipFireLocation = FVector(1.575968f,11.798502f,-153.145187f);
	//(Pitch=3.000000,Yaw=-12.000000,Roll=0.000000)
	FRotator HipFireRotation = FRotator(3.000000f,-12.000000f,0.000000f);

public:
	virtual void ConstructShotVectors() override;

protected:
	virtual FVector GetAimDownSightsLocation() override;

	virtual FRotator GetAimDownSightsRotation() override;

	virtual FVector GetHipFireLocation() override;

	virtual FRotator GetHipFireRotation() override;
};
