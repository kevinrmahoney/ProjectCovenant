// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Sniper.h"
#include "ItemWeapon.h"
#include "SubjectZero.h"
#include "HumanController.h"

ASniper::ASniper()
{
	PrimaryActorTick.bCanEverTick = true;
	AimDownSightsFieldOfView = 10.f;
}

// Called when the game starts or when spawned
void ASniper::BeginPlay()
{
	Super::BeginPlay();
	//TODO: adjust values for shotgun
}

void ASniper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASniper::Update()
{
	// If the trigger is pulled
	if (Trigger)
	{
		// If the cooldown has passed
		if (TimeSinceLastShot > Cooldown)
		{
			// Shoot the weapon
			Shoot();
			if (RecoilComponent)
			{
				RecoilComponent->Recoil();
			}
			// Subtract the cooldown from the time passed since the last shot.
			// make sure the outcome does not go above value of Cooldown
			TimeSinceLastShot = 0.f;
			if (Item)
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

void ASniper::ConstructShotVectors()
{
	ShotVectors.Add(FVector(Range, 0.f, 0.f));
}

void ASniper::Shoot()
{
	PlayShootSound();

	if (Shooter->HasAuthority())
	{
		float TotalDamage = 0.f;
		int count = 0;

		AProjectile * NewProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Muzzle->GetComponentLocation(), Muzzle->GetComponentRotation());
		if (NewProjectile)
		{
			NewProjectile->SetWeapon(this);
			NewProjectile->SetDamage(Damage);
		}
	}
}

void ASniper::DealDamage(ASubjectZero * Victim, float TotalDamage)
{
	Super::DealDamage(Victim, TotalDamage);
}

void ASniper::AimDownSights(bool IsAimDownSights) 
{
	Super::AimDownSights(IsAimDownSights);
	if (IsAimDownSights)
	{
		if(Shooter && Shooter->Camera) Shooter->Camera->FieldOfView = AimDownSightsFieldOfView;
		if (GunMesh) GunMesh->SetVisibility(false);
		if(Shooter && Shooter->FirstPersonMesh) Shooter->FirstPersonMesh->SetVisibility(false);
	}
	else
	{
		if(Shooter && Shooter->Camera) Shooter->Camera->FieldOfView = Shooter->DefaultFieldOfView;
		if (GunMesh) GunMesh->SetVisibility(true);
		if (Shooter && Shooter->FirstPersonMesh) Shooter->FirstPersonMesh->SetVisibility(true);
	}
	AHumanController * Human = Cast<AHumanController>(Shooter->GetController());
	if (Human)
	{
		Human->DrawZoomCrosshair(IsAimDownSights);
	}
}

FVector ASniper::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator ASniper::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector ASniper::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator ASniper::GetHipFireRotation()
{
	return HipFireRotation;
}

