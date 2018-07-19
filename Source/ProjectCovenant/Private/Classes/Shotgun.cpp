// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Shotgun.h"
#include "SubjectZero.h"

AShotgun::AShotgun()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 80.f;
	MaximumRange = 20000.f;
	FireRate = 1.f;
	HeatThreshold = 100.f;
	OverHeatPenalty = 50.f;
	FallOff = 1.f;
	HeatGeneratedPerShot = 25.f;
}

// Called when the game starts or when spawned
void AShotgun::BeginPlay() 
{
	Super::BeginPlay();
	Damage = Damage / ShotVectors.Num();
}

void AShotgun::ConstructShotVectors()
{
	for(int i = 1; i <= CircleCount; i++)
	{
		FVector SpreadVector;
		for(int j = 0; j < RollCount; j++)
		{
			SpreadVector = FVector(MaximumRange, MaxConeAngle / i, 0.f);
			SpreadVector = SpreadVector.RotateAngleAxis(360 / RollCount * j, FVector(1.f, 0.f, 0.f));
			ShotVectors.Add(SpreadVector);
		}
	}
}

void AShotgun::Fire()
{
	Super::Fire();
	DrawDebugVisuals();
}

FVector AShotgun::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator AShotgun::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector AShotgun::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator AShotgun::GetHipFireRotation()
{
	return HipFireRotation;
}