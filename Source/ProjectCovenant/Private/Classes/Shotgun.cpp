// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Shotgun.h"
#include "ItemWeapon.h"
#include "SubjectZero.h"

AShotgun::AShotgun()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 100.f;
	Range = 20000.f;
	FireRate = 1.f;
	Reload = 2.f;
	FallOff = 1.f;
	AmmoMax = 6.f;
	Ammo = AmmoMax;
}

// Called when the game starts or when spawned
void AShotgun::BeginPlay() 
{
	Super::BeginPlay();
	Damage = Damage / ShotVectors.Num();
}

void AShotgun::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
}

void AShotgun::ConstructShotVectors()
{
	for(int i = 1; i <= CircleCount; i++)
	{
		FVector SpreadVector;
		for(int j = 0; j < RollCount; j++)
		{
			SpreadVector = FVector(Range, MaxConeAngle / i, 0.f);
			SpreadVector = SpreadVector.RotateAngleAxis(360 / RollCount * j, FVector(1.f, 0.f, 0.f));
			ShotVectors.Add(SpreadVector);
		}
	}
}

void AShotgun::Update(float DeltaTime)
{
	Super::Update(DeltaTime);
}

void AShotgun::Fire()
{
	Super::Fire();
	DrawDebugVisuals();
	Ammo--;
}

void AShotgun::Shoot()
{
	Super::Fire();
	Ammo--;
}

void AShotgun::DealDamage(ASubjectZero * Victim, float TotalDamage)
{
	Super::DealDamage(Victim, TotalDamage);
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