// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileWeapon.h"
#include "GrapplingHook.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API AGrapplingHook : public AProjectileWeapon
{
	GENERATED_BODY()
		
public:
	AGrapplingHook ();
	virtual void Fire() override;
	virtual void Tick(float DeltaTime) override;

	//(X=1.575968,Y=11.798502,Z=-153.145187)
	FVector HipFireLocation = FVector(1.575968f, 11.798502f, -153.145187f);
	//(Pitch=3.000000,Yaw=-12.000000,Roll=0.000000)
	FRotator HipFireRotation = FRotator(3.000000f, -12.000000f, 0.000000f);

protected:
	virtual FVector GetHipFireLocation() override;
	virtual FRotator GetHipFireRotation() override;
	bool CanFire() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChainDistance = 3000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDistancePerSecond = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GrappleCutoffDistance = 300;
	
	UPROPERTY()
	float GrappleTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GrappleTimeMax = 2.f;

private:
	virtual void ConstructShotVectors() override;
	void Grapple(float DeltaTime);
	FVector TargetLocation = FVector::ZeroVector;
	bool IsLatched = false;
	bool HasFired = false;

};
