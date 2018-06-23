// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "PlasmaWeapon.h"
#include "BasePlayerState.h"
#include "SubjectZero.h"
#include "HumanController.h"
#include "UnrealNetwork.h"
#include "ItemWeapon.h"
#include "BaseMode.h"

// Sets default values
APlasmaWeapon::APlasmaWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlasmaWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlasmaWeapon::Tick(float DeltaTime)
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

void APlasmaWeapon::Update(float DeltaTime)
{

}

bool APlasmaWeapon::CanFire()
{
	return Ammo > 0.f && FireRateProgress > FireRate && ReloadProgress == 0.f;
}

void APlasmaWeapon::Fire()
{

}

void APlasmaWeapon::ConstructShotVectors()
{
}

void APlasmaWeapon::Shoot()
{

}

void APlasmaWeapon::DrawDebugVisuals()
{

}

void APlasmaWeapon::DealDamage(ASubjectZero * Victim, float TotalDamage)
{

}

FVector APlasmaWeapon::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator APlasmaWeapon::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector APlasmaWeapon::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator APlasmaWeapon::GetHipFireRotation()
{
	return HipFireRotation;
}


