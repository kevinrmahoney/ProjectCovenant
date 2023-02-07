// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "LightningGun.h"
#include "BasePlayerState.h"
#include "SubjectZero.h"
#include "HumanController.h"
#include "ItemWeapon.h"
#include "BaseMode.h"

// Sets default values
ALightningGun::ALightningGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 6.f;
	MaximumRange = 20000.f;
	FireRate = 0.1f;
	HeatThreshold = 100.f;
	OverHeatPenalty = 50.f;
	FallOff = 1.f;
	HeatGeneratedPerShot = 2.5f;
}

// Called when the game starts or when spawned
void ALightningGun::BeginPlay()
{
	Super::BeginPlay();
}

void ALightningGun::ConstructShotVectors()
{
	ShotVectors.Add(FVector(MaximumRange, 0.f, 0.f));
}

// Called every frame
void ALightningGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsCoolingDown || !Trigger)
	{
		StopSoundAndVisuals();
	}
}

FVector ALightningGun::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator ALightningGun::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector ALightningGun::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator ALightningGun::GetHipFireRotation()
{
	return HipFireRotation;
}
