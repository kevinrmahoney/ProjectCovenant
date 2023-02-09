// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "RocketLauncher.h"
#include "ItemWeapon.h"
#include "SubjectZero.h"

ARocketLauncher::ARocketLauncher()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 120.f;
	FireRate = 1.f;
	Reload = 2.f;
	AmmoMax = 4.f;
	Ammo = AmmoMax;
	ProjectileSpeed = 4000.f;
}

FVector ARocketLauncher::GetAimDownSightsLocation()
{
	return HipFireLocation;
}

FRotator ARocketLauncher::GetAimDownSightsRotation()
{
	return HipFireRotation;
}

FVector ARocketLauncher::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator ARocketLauncher::GetHipFireRotation()
{
	return HipFireRotation;
}