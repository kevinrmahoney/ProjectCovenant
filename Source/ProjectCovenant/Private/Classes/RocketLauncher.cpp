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
	ShotVectors.Add(FVector(Range, 0.f, 0.f));

	Damage = 120.f;
	Range = 20000.f;
	Cooldown = 1.f;
	ReloadTime = 2.f;
	FallOff = 1.f;
	AmmoMax = 4.f;
	Ammo = AmmoMax;
}

void ARocketLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARocketLauncher::Update()
{
	if(Ammo > 0)
	{
		// If the trigger is pulled
		if(Trigger)
		{
			// If the cooldown has passed
			if(TimeSinceLastShot > Cooldown)
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
				TimeSinceLastShot = 0.f;
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