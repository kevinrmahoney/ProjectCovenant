// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "RocketLauncher.h"
#include "ItemWeapon.h"
#include "SubjectZero.h"

ARocketLauncher::ARocketLauncher()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 120.f;
	Range = 20000.f;
	FireRate = 1.f;
	Reload = 2.f;
	FallOff = 1.f;
	AmmoMax = 4.f;
	Ammo = AmmoMax;
}

// Called when the game starts or when spawned
void ARocketLauncher::BeginPlay()
{
	Super::BeginPlay();
}

void ARocketLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARocketLauncher::Update(float DeltaTime)
{
	if(Ammo > 0)
	{
		// If the trigger is pulled
		if(Trigger)
		{
			// If the cooldown has passed
			if(FireRateProgress > FireRate)
			{
				Ammo--;
				// Shoot the weapon
				Shoot();
				if(RecoilComponent)
				{
					RecoilComponent->Recoil();
				}

				// Subtract the cooldown from the time passed since the last shot.
				// make sure the outcome does not go above value of Cooldown
				FireRateProgress = 0.f;
				if(Item)
				{
					Item->SetLastShotTimeStamp(GetWorld());
				}
				else
				{
					Logger::Log("No item is associated with this weapon");
				}
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