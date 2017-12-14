// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitscanWeapon.generated.h"

UCLASS()
class PROJECTCOVENANT_API AHitscanWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitscanWeapon();

private:
	float Damage = 10.f;
	float Range = 10000.f;
	float TimeBetweenShot = 0.1f;
	float TimeSinceLastShot = 0.f;
	float Falloff = 1.f;
	float Ammo = 100.f;
	bool Trigger = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	void Shoot();

	void SetTrigger(bool T);
	
};