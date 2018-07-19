// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Railgun.h"
#include "BasePlayerState.h"
#include "SubjectZero.h"

// Sets default values
ARailgun::ARailgun()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 100.f;
	MaximumRange = 20000.f;
	FireRate = 1.f;
	HeatThreshold = 100.f;
	OverHeatPenalty = 25.f;
	FallOff = 1.f;
	HeatGeneratedPerShot = HeatThreshold;
}
void ARailgun::ConstructShotVectors()
{
	ShotVectors.Add(FVector(MaximumRange, 0.f, 0.f));
}

FVector ARailgun::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator ARailgun::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector ARailgun::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator ARailgun::GetHipFireRotation()
{
	return HipFireRotation;
}