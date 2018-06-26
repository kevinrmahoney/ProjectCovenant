// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/PlasmaWeapon.h"
#include "PlasmaCannon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API APlasmaCannon : public APlasmaWeapon
{
	GENERATED_BODY()
	
public:
	APlasmaCannon();

	bool IsCharging = false;

	//(X=1.575968,Y=11.798502,Z=-153.145187)
	FVector AimDownSightsLocation = FVector(1.575968f, 11.798502f, -153.145187f);
	//(Pitch=3.000000,Yaw=-12.000000,Roll=0.000000)
	FRotator AimDownSightsRotation = FRotator(3.000000f, -12.000000f, 0.000000f);

	//(X=1.575968,Y=11.798502,Z=-153.145187)
	FVector HipFireLocation = FVector(1.575968f, 11.798502f, -153.145187f);
	//(Pitch=3.000000,Yaw=-12.000000,Roll=0.000000)
	FRotator HipFireRotation = FRotator(3.000000f, -12.000000f, 0.000000f);

	virtual void SetTrigger(bool T) override;

	virtual void Update(float DeltaTime) override;

	virtual bool CanFire() override;

	virtual void Fire() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeatRateWhileCharging;

	virtual void AimDownSights(bool IsAimDownSights) override;

	virtual FVector GetAimDownSightsLocation() override;

	virtual FRotator GetAimDownSightsRotation() override;

	virtual FVector GetHipFireLocation() override;

	virtual FRotator GetHipFireRotation() override;
};
