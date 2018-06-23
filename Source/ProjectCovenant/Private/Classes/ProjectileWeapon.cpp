// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "ProjectileWeapon.h"
#include "BasePlayerState.h"
#include "SubjectZero.h"
#include "HumanController.h"
#include "UnrealNetwork.h"
#include "ItemWeapon.h"
#include "BaseMode.h"

// Sets default values
AProjectileWeapon::AProjectileWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectileWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileWeapon::Update(float DeltaTime)
{
	Super::Update(DeltaTime);
}

bool AProjectileWeapon::CanFire()
{
	return Ammo > 0.f && !IsReloading && FireRateProgress >= FireRate;
}

void AProjectileWeapon::Fire()
{
	Super::Fire();


	if(Shooter->HasAuthority())
	{
		AProjectile * NewProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Muzzle->GetComponentLocation(), Muzzle->GetComponentRotation());
		if(NewProjectile)
		{
			NewProjectile->SetWeapon(this);
			NewProjectile->SetDamage(Damage);
		}
	}
	Ammo--;
}

void AProjectileWeapon::ConstructShotVectors()
{
}

void AProjectileWeapon::DrawDebugVisuals()
{

}

void AProjectileWeapon::DealDamage(ASubjectZero * Victim, float TotalDamage)
{

}

FVector AProjectileWeapon::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator AProjectileWeapon::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector AProjectileWeapon::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator AProjectileWeapon::GetHipFireRotation()
{
	return HipFireRotation;
}
