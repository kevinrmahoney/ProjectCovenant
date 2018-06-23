// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "ProjectileWeapon.h"
#include "BasePlayerState.h"
#include "SubjectZero.h"
#include "HumanController.h"
#include "UnrealNetwork.h"
#include "ItemWeapon.h"
#include "BaseMode.h"

// Sets default values
AProjectileWeapon::AProjectileWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectileWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FireRateProgress += DeltaTime;
	if(ReloadProgress > 0.f)
	{
		ReloadProgress = ReloadProgress - DeltaTime;
		if(ReloadProgress <= 0.f)
		{
			Ammo = AmmoMax;
		}
	}
	else
	{
		Update(DeltaTime);
	}
}

void AProjectileWeapon::Update(float DeltaTime)
{

}

bool AProjectileWeapon::CanFire()
{
	return Ammo > 0.f && FireRateProgress > FireRate && ReloadProgress == 0.f;
}

void AProjectileWeapon::Fire()
{

}

void AProjectileWeapon::ConstructShotVectors()
{
}

void AProjectileWeapon::Shoot()
{
	
}

void AProjectileWeapon::DrawDebugVisuals()
{

}

void AProjectileWeapon::DealDamage(ASubjectZero * Victim, float TotalDamage)
{

}

FVector AProjectileWeapon::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator AProjectileWeapon::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector AProjectileWeapon::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator AProjectileWeapon::GetHipFireRotation()
{
	return HipFireRotation;
}
