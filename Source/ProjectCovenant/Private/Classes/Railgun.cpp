// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Railgun.h"
#include "BasePlayerState.h"
#include "ItemWeapon.h"
#include "SubjectZero.h"

// Sets default values
ARailgun::ARailgun()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 100.f;
	Range = 20000.f;
	FireRate = 2.f;
	Reload = 2.f;
	FallOff = 1.f;
	AmmoMax = 1.f;
	Ammo = AmmoMax;
}

// Called when the game starts or when spawned
void ARailgun::BeginPlay()
{
	Super::BeginPlay();
}

void ARailgun::ConstructShotVectors()
{
	ShotVectors.Add(FVector(Range, 0.f, 0.f));
}

void ARailgun::Fire()
{
	Super::Fire();

	// Railgun only has one bullet, so set to zero, and automatically begin reloading
	Ammo = 0.f;
	BeginReload();
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