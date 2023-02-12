// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "PlasmaCannon.h"
#include "ItemWeapon.h"
#include "SubjectZero.h"
#include "HumanController.h"
#include "Projectile.h"

APlasmaCannon::APlasmaCannon()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 75.f;
	FireRate = 0.3f;
	HeatThreshold = 150.f;
	OverHeatPenalty = 100.f;
	HeatGeneratedPerShot = 0.f;
	ProjectileSpeed = 3000.f;
	HeatRateWhileCharging = 50.f;

	ShotVectors.Add(FVector(20000.f, 0.f, 0.f));
}

void APlasmaCannon::Destroyed()
{
	IsCharging = false;
	if(Trigger && CanFire())
	{
		Fire();
	}
	Super::Destroyed();
}

void APlasmaCannon::Update(float DeltaTime)
{
	FireRateProgress = FireRateProgress + DeltaTime;
	WeaponSwitchCooldownProgress = WeaponSwitchCooldownProgress + DeltaTime;

	// If being forced to cooldown or cooling down after a shot
	if(IsCoolingDown || FireRateProgress >= FireRate + CooldownPause && !IsCharging)
	{
		Heat = FMath::Max(Heat - CooldownRate * DeltaTime, 0.f);
		if(Heat == 0.f)
		{
			IsCharging = Trigger;
		}
	}

	// Stop cooling down if heat is below zero
	if(IsCoolingDown && Heat <= 0.f)
	{
		IsCoolingDown = false;
	}

	if(IsCharging)
	{
		Heat += DeltaTime * HeatRateWhileCharging;
	}

	if(Heat >= HeatThreshold && IsCharging)
	{
		Fire();
	}
}

void APlasmaCannon::SetTrigger(bool T) 
{
	// If you just pulled the trigger
	if(!Trigger && T && !IsCoolingDown)
	{
		IsCharging = true;
	}
	// If you just let go of the trigger
	else if(Trigger && !T)
	{
		IsCharging = false;
		if(CanFire())
		{
			Fire();
		}
	}
	Super::SetTrigger(T);
}

bool APlasmaCannon::CanFire() 
{
	return !IsCharging && Super::CanFire();
}

void APlasmaCannon::Fire()
{
	// Reset FireRateProgress and add heat
	FireRateProgress = 0.f;
	Heat = Heat + HeatGeneratedPerShot;
	IsCharging = false;

	// If heat added is greater than the heat threshold,
	// add an extra heat penalty and begin the forced cooldown process
	if(Heat >= HeatThreshold)
	{
		Heat = Heat + OverHeatPenalty;
	}

	BeginCooldown();

	if(Shooter && Shooter->HasAuthority())
	{
		AProjectile * NewProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Muzzle->GetComponentLocation(), Muzzle->GetComponentRotation());
		if(NewProjectile)
		{
			NewProjectile->SetActorScale3D(FVector(1.f) * (MaxScale * Heat / HeatThreshold));
			NewProjectile->SetWeapon(this);
			NewProjectile->SetDamage(Damage * Heat / HeatThreshold);
			NewProjectile->SetSpeed(ProjectileSpeed + ProjectileSpeed * Heat / HeatThreshold);
		}
	}

	// Apply recoil
	if(RecoilComponent)
	{
		RecoilComponent->Recoil(Heat / HeatThreshold);
	}

	// Draw visuals and play sounds
	DrawVisuals();
	PlayShootSound();
}

void APlasmaCannon::AimDownSights(bool IsAimDownSights)
{
	Super::AimDownSights(IsAimDownSights);
}

FVector APlasmaCannon::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator APlasmaCannon::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector APlasmaCannon::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator APlasmaCannon::GetHipFireRotation()
{
	return HipFireRotation;
}