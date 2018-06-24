// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/PlasmaWeapon.h"
#include "PlasmaCarbine.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API APlasmaCarbine : public APlasmaWeapon
{
	GENERATED_BODY()
	
public:
	APlasmaCarbine();

	//(X=-3.327673,Y=-8.630527,Z=-132.148392)
	FVector AimDownSightsLocation = FVector(-3.327673f, -8.630527f, -132.148392f);
	//(Pitch=2.999819,Yaw=-12.000000,Roll=0.000007)
	FRotator AimDownSightsRotation = FRotator(2.999819f, -12.000000f, 0.000007f);

	//(X=1.575968,Y=11.798502,Z=-153.145187)
	FVector HipFireLocation = FVector(1.575968f, 11.798502f, -153.145187f);
	//(Pitch=3.000000,Yaw=-12.000000,Roll=0.000000)
	FRotator HipFireRotation = FRotator(3.000000f, -12.000000f, 0.000000f);

protected:
	virtual void AimDownSights(bool IsAimDownSights) override;

	virtual FVector GetAimDownSightsLocation() override;

	virtual FRotator GetAimDownSightsRotation() override;

	virtual FVector GetHipFireLocation() override;

	virtual FRotator GetHipFireRotation() override;
	
	
};
