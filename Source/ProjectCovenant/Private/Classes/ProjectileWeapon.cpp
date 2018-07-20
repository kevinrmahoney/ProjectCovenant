// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "ProjectileWeapon.h"
#include "BasePlayerState.h"
#include "SubjectZero.h"
#include "HumanController.h"
#include "UnrealNetwork.h"
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

void AProjectileWeapon::Destroyed()
{
	if(Item)
	{
		Item->Ammo = Ammo;
	}

	Super::Destroyed();
}

void AProjectileWeapon::SetItem(UItem * NewItem)
{
	if(Role == ROLE_Authority || Role == ROLE_AutonomousProxy)
	{
		if(NewItem)
		{
			// Calculate how long its been since the last shot
			Item = NewItem;
			float TimeSinceLastShot = UGameplayStatics::GetRealTimeSeconds(GetWorld()) - Item->LastShotTimeStamp;
			float TimeSinceUnequip = UGameplayStatics::GetRealTimeSeconds(GetWorld()) - Item->UnequipTimeStamp;
			
			Ammo = Item->Ammo;
			FireRateProgress = TimeSinceLastShot;

			// Based on the newly set variables, recalculate weapon's variables accounting for the time since the weapon has been shot.
			WeaponSwitchCooldownProgress = 0.f;
		}
		else
		{
			Logger::Error("Attempting to set NULL item for " + GetName());
		}
	}
}

// Called every frame
void AProjectileWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileWeapon::Update(float DeltaTime)
{
	FireRateProgress = FireRateProgress + DeltaTime;
	WeaponSwitchCooldownProgress = WeaponSwitchCooldownProgress + DeltaTime;

	if(IsReloading)
	{
		ReloadProgress = ReloadProgress + DeltaTime;
		if(ReloadProgress >= Reload)
		{
			Ammo = AmmoMax;
			IsReloading = false;
		}
	}
}

bool AProjectileWeapon::CanFire()
{
	return Ammo > 0.f && !IsReloading && FireRateProgress >= FireRate && Super::CanFire();
}

void AProjectileWeapon::Fire()
{
	Super::Fire();

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
	Ammo--;
}

void AProjectileWeapon::BeginReload()
{
	if(Ammo < AmmoMax && !IsReloading)
	{
		IsReloading = true;
		ReloadProgress = 0.f;
	}
}

float AProjectileWeapon::GetAmmo()
{
	return Ammo;
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