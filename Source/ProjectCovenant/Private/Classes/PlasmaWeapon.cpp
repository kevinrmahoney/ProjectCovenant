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

void APlasmaWeapon::Destroyed()
{
	if(Item)
	{
		Item->IsCoolingDown = IsCoolingDown;
		Item->Heat = Heat;
	}

	Super::Destroyed();
}

void APlasmaWeapon::SetItem(UItem * NewItem)
{
	if(Role == ROLE_Authority || Role == ROLE_AutonomousProxy)
	{
		if(NewItem)
		{
			// Calculate how long its been since the last shot
			Item = NewItem;
			float TimeSinceLastShot = UGameplayStatics::GetRealTimeSeconds(GetWorld()) - Item->LastShotTimeStamp;

			// WeaponSwitchCooldown represents a global cooldown for switching weapons. Wait at least this amount of time
			// before allowing the gun to shoot. Wait a greater amount of time if the TimeSinceLastShot is longer
			FireRateProgress = FireRateProgress + TimeSinceLastShot;

			Heat = NewItem->Heat;
			IsCoolingDown = NewItem->IsCoolingDown;

			// Based on the newly set variables, recalculate weapon's variables accounting for the time since the weapon has been shot.
			WeaponSwitchCooldownProgress = -TimeSinceLastShot;
			Update(TimeSinceLastShot);
		}
		else
		{
			Logger::Error("Attempting to set NULL item for " + GetName());
		}
	}
}

void APlasmaWeapon::Update(float DeltaTime)
{
	FireRateProgress = FireRateProgress + DeltaTime;
	WeaponSwitchCooldownProgress = WeaponSwitchCooldownProgress + DeltaTime;

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
	return FireRateProgress >= FireRate && !IsCoolingDown && Super::CanFire();
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

	if(Shooter && Shooter->HasAuthority())
	{
		AProjectile * NewProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Muzzle->GetComponentLocation(), Muzzle->GetComponentRotation());
		if(NewProjectile)
		{
			NewProjectile->SetWeapon(this);
			NewProjectile->SetDamage(Damage);
			NewProjectile->SetSpeed(ProjectileSpeed);
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