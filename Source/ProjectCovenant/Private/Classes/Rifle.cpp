// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Rifle.h"
#include "ItemWeapon.h"
#include "SubjectZero.h"

ARifle::ARifle()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 30.f;
	Range = 20000.f;
	Cooldown = 0.2f;
	ReloadTime = 2.f;
	FallOff = 1.f;
	AmmoMax = 20.f;
	Ammo = AmmoMax;
}

// Called when the game starts or when spawned
void ARifle::BeginPlay()
{
	Super::BeginPlay();
}

void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARifle::Update()
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

void ARifle::ConstructShotVectors()
{
	ShotVectors.Add(FVector(Range, 0.f, 0.f));
}

void ARifle::Shoot()
{
	PlayShootSound();
	
	if(Shooter->HasAuthority())
	{
		float TotalDamage = 0.f;
		int count = 0;

		AProjectile * NewProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Muzzle->GetComponentLocation(), Muzzle->GetComponentRotation());
		if(NewProjectile)
		{
			NewProjectile->SetWeapon(this);
			NewProjectile->SetDamage(Damage);
		}
	}
}

void ARifle::DealDamage(ASubjectZero * Victim, float TotalDamage)
{
	Super::DealDamage(Victim, TotalDamage);
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
