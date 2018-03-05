// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/HitscanWeapon.h"
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

	//(X=-14.290447,Y=-0.018228,Z=-143.514786)
	FVector HipfireLocation = FVector(-14.290447f, -0.018228f, -143.514786f);
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

protected:
	void Shoot() override;

	void DealDamage(ASubjectZero * Victim, float TotalDamage) override;

	void DrawLaser() override;

};
