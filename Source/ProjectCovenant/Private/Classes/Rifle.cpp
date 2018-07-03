// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Rifle.h"
#include "ItemWeapon.h"
#include "SubjectZero.h"

ARifle::ARifle()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 20.f;
	FireRate = 0.2f;
	Reload = 2.f;
	AmmoMax = 20.f;
	Ammo = AmmoMax;
	ProjectileSpeed = 6000.f;
}

FVector ARifle::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator ARifle::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector ARifle::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator ARifle::GetHipFireRotation()
{
	return HipFireRotation;
}
