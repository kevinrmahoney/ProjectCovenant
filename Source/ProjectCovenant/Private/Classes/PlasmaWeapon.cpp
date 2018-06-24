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

void APlasmaWeapon::Update(float DeltaTime)
{
	FireRateProgress = FireRateProgress + DeltaTime;

	// If being forced to cooldown or cooling down after a shot
	if(IsCoolingDown || FireRateProgress >= FireRate + CooldownPause)
	{
		Heat = FMath::Max(Heat - CooldownRate * DeltaTime, 0.f);
	}

	// Stop cooling down if heat is below zero
	if(IsCoolingDown && Heat <= 0.f)
	{
		IsCoolingDown = false;
	}
}

bool APlasmaWeapon::CanFire()
{
	return FireRateProgress >= FireRate && !IsCoolingDown;
}

void APlasmaWeapon::Fire()
{
	Super::Fire();

	// Reset FireRateProgress and add heat
	FireRateProgress = 0.f;
	Heat = Heat + HeatGeneratedPerShot;

	// If heat added is greater than the heat threshold,
	// add an extra heat penalty and begin the forced cooldown process
	if(Heat >= HeatThreshold)
	{
		Heat = Heat + OverHeatPenalty;
		BeginCooldown();
	}

	if(HasAuthority())
	{
		AProjectile * NewProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Muzzle->GetComponentLocation(), Muzzle->GetComponentRotation());
		if(NewProjectile)
		{
			NewProjectile->SetWeapon(this);
			NewProjectile->SetDamage(Damage);
		}
	}
}

void APlasmaWeapon::BeginCooldown()
{
	IsCoolingDown = true;
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


