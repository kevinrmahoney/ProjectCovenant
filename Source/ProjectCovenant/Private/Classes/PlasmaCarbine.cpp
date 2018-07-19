// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "PlasmaCarbine.h"
#include "SubjectZero.h"
#include "HumanController.h"

APlasmaCarbine::APlasmaCarbine()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AimDownSightsFieldOfView = 20.f;
	Damage = 30.f;
	FireRate = 0.3f;
	HeatThreshold = 120.f;
	OverHeatPenalty = 50.f;
	HeatGeneratedPerShot = 20.f;
	ProjectileSpeed = 20000.f;

	ShotVectors.Add(FVector(20000.f, 0.f, 0.f));
}


void APlasmaCarbine::AimDownSights(bool IsAimDownSights)
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

FVector APlasmaCarbine::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator APlasmaCarbine::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector APlasmaCarbine::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator APlasmaCarbine::GetHipFireRotation()
{
	return HipFireRotation;
}