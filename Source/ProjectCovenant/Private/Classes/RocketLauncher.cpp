// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "RocketLauncher.h"
#include "ItemWeapon.h"
#include "SubjectZero.h"

ARocketLauncher::ARocketLauncher()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARocketLauncher::BeginPlay()
{
	Super::BeginPlay();
	//TODO: adjust values for shotgun
	Damage = 100.f;
	Range = 5000.f;
	Cooldown = 1.f;
	FallOff = 1.f; //not yet implemented, less damage depending on distance. 1 = 100%
				   //TODO lower ammo count, but don't disable shooting with negative ammo yet
	Ammo = 100.f; //not yet implemented 
	Duration = 0.25;
	ShotVectors.Add(FVector(Range, 0.f, 0.f));
	TimeSinceLastShot = Cooldown;
}

void ARocketLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARocketLauncher::Update()
{
	// If the trigger is pulled
	if(Trigger)
	{
		// If the cooldown has passed
		if(TimeSinceLastShot > Cooldown)
		{
			// Shoot the weapon
			Shoot();

			// Subtract the cooldown from the time passed since the last shot.
			// make sure the outcome does not go above value of Cooldown
			TimeSinceLastShot = 0.f;
			if(Item)
			{
				Item->SetLastShotTimeStamp(GetWorld());
			}
		}
	}
}

void ARocketLauncher::ConstructShotVectors()
{
	ShotVectors.Add(FVector(Range, 0.f, 0.f));
}

void ARocketLauncher::Shoot()
{
	PlayShootSound();

	if(Shooter->HasAuthority())
	{
		float TotalDamage = 0.f;
		int count = 0;

		ASubjectZero * Victim = nullptr;

		AProjectile * NewProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Muzzle->GetComponentLocation(), Muzzle->GetComponentRotation());
		if(NewProjectile)
		{
			NewProjectile->SetWeapon(this);
		}

		if(Victim)
		{
			DealDamage(Victim, TotalDamage);
		}
	}
}

void ARocketLauncher::DealDamage(ASubjectZero * Victim, float TotalDamage)
{
	Super::DealDamage(Victim, TotalDamage);
}

FVector ARocketLauncher::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator ARocketLauncher::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector ARocketLauncher::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator ARocketLauncher::GetHipFireRotation()
{
	return HipFireRotation;
}