// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Sniper.h"
#include "SubjectZero.h"
#include "HumanController.h"

ASniper::ASniper()
{
	PrimaryActorTick.bCanEverTick = true;

	AimDownSightsFieldOfView = 10.f;
	Damage = 120.f;
	FireRate = 2.f;
	Reload = 2.f;
	AmmoMax = 1.f;
	Ammo = AmmoMax;
	ProjectileSpeed = 12000.f;
}

void ASniper::AimDownSights(bool IsAimDownSights)
{
	Super::AimDownSights(IsAimDownSights);

	if(Shooter && Shooter->IsLocallyControlled())
	{
		if(IsAimDownSights)
		{
			if(Shooter->Camera) Shooter->Camera->FieldOfView = AimDownSightsFieldOfView;
			if(GunMesh) GunMesh->SetVisibility(false);
			if(Shooter->FirstPersonMesh) Shooter->FirstPersonMesh->SetVisibility(false);
		}
		else
		{
			if(Shooter->Camera) Shooter->Camera->FieldOfView = Shooter->DefaultFieldOfView;
			if(GunMesh) GunMesh->SetVisibility(true);
			if(Shooter->FirstPersonMesh) Shooter->FirstPersonMesh->SetVisibility(true);
		}

		if(AHumanController * Human = Cast<AHumanController>(Shooter->GetController()))
		{
			Human->DrawZoomCrosshair(IsAimDownSights);
		}
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


