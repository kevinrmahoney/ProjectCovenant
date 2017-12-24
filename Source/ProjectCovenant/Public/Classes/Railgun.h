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

private:
	void Shoot() override;

	void DealDamage(ASubjectZero * Victim) override;

	void DrawLaser(FVector * Begin, FVector * End, float Duration) override;

};
