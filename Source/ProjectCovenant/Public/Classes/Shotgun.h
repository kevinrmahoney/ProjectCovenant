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

	//(X=0.429121,Y=-2.596338,Z=-145.296036)
	FVector HipfireLocation = FVector(0.429121f, -2.596338f, -145.296036f);
	//(Pitch=2.812467,Yaw=-19.000458,Roll=0.000000)
	FRotator HipfireRotation = FRotator(2.812467f, -19.000458f, 0.000000f);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTrigger(bool T);

	void SetShooter(ASubjectZero * NewShooter);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayShootSound();

	virtual FVector GetAimDownSightsLocation() override;

	virtual FRotator GetAimDownSightsRotation() override;

private:
	void Shoot() override;

	void DealDamage(ASubjectZero * Victim, float TotalDamage) override;

	void DrawLaser() override;

	float MaxConeAngle = 200.f;

	//maybe change to FRotator
	float RollCount = 8.f;

	float CircleCount = 2.f;

	TArray<FVector> Spread;
};
