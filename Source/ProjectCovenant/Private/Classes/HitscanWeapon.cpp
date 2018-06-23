// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HitscanWeapon.h"
#include "BasePlayerState.h"
#include "SubjectZero.h"
#include "HumanController.h"
#include "ItemWeapon.h"
#include "BaseMode.h"

// Sets default values
AHitscanWeapon::AHitscanWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHitscanWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHitscanWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHitscanWeapon::Update(float DeltaTime)
{
	FireRateProgress = FMath::Clamp(FireRateProgress + DeltaTime, 0.f, FireRate);

	if(IsReloading && FireRateProgress >= FireRate)
	{
		ReloadProgress = FMath::Clamp(ReloadProgress + DeltaTime, 0.f, Reload);
		if(ReloadProgress >= Reload)
		{
			Ammo = AmmoMax;
			IsReloading = false;
		}
	}

	if(!(CanFire() && Trigger) && FireRateProgress >= FireRate && !IsReloading)
	{
		ReloadProgress = FMath::Clamp(ReloadProgress + DeltaTime, 0.f, Reload);
	}
}

bool AHitscanWeapon::CanFire()
{
	return FireRateProgress >= FireRate && !IsReloading;
}

void AHitscanWeapon::Fire()
{
	Super::Fire();

	ReloadProgress = FMath::Clamp(ReloadProgress - (Reload / AmmoMax), 0.f, Reload);
	if(ReloadProgress <= 0.f) BeginReload();

	if(HasAuthority())
	{
		ASubjectZero * Victim = nullptr;
		float TotalDamage = 0.f;

		//for loop for radius of circle and nested for loop for roll
		for(FVector Shot : ShotVectors)
		{
			FVector * StartTrace = new FVector(Muzzle->GetComponentLocation());
			FVector * EndTrace = new FVector(*StartTrace + FVector(Muzzle->GetComponentRotation().RotateVector(Shot)));
			FHitResult* HitResult = new FHitResult();
			FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
			TraceParams->AddIgnoredActor(Shooter);	// Ignore the Shooter when doing the trace (can't shoot yourself)

			// If firing a round, do a line trace in front of the gun, check if there is a hit, and check if that hit is an actor
			if(GetWorld()->LineTraceSingleByChannel(*HitResult, *StartTrace, *EndTrace, ECC_Pawn, *TraceParams) && HitResult && HitResult->GetActor())
			{
				// Get the victim and attempt to cast to SubjectZero
				if(!Victim)
				{
					Victim = Cast<ASubjectZero>(HitResult->GetActor());
				}
				TotalDamage += Damage;
			}

			delete HitResult;
			delete TraceParams;
			delete StartTrace;
			delete EndTrace;
		}

		if(Victim && Shooter)
		{
			DealDamage(Victim, TotalDamage);
		}
	}
}

void AHitscanWeapon::BeginReload()
{
	if(ReloadProgress <= 0.f)
	{
		IsReloading = true;
		ReloadProgress = 0.f;
	}
	else
	{
		Logger::Chat("Cant reload");
	}
}

void AHitscanWeapon::ConstructShotVectors()
{
}

void AHitscanWeapon::DrawDebugVisuals()
{
	FVector StartPoint = FVector(Muzzle->GetComponentLocation());
	FVector EndPoint;
	for(FVector V : ShotVectors)
	{
		EndPoint = StartPoint + FVector(Muzzle->GetComponentRotation().RotateVector(V));
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, FireRate);
	}
}

void AHitscanWeapon::DealDamage(ASubjectZero * Victim, float TotalDamage)
{
	Super::DealDamage(Victim, TotalDamage);
}

FVector AHitscanWeapon::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator AHitscanWeapon::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector AHitscanWeapon::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator AHitscanWeapon::GetHipFireRotation()
{
	return HipFireRotation;
}
