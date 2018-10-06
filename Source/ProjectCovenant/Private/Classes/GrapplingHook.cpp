// Fill out your copyright notice in the Description page of Project Settings.

//AddMovementInput(Rotation.RotateVector(GroundMove.GetSafeNormal()), 1.f);

#include "ProjectCovenant.h"
#include "GrapplingHook.h"

AGrapplingHook::AGrapplingHook()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 20.f;
	FireRate = 0.2f;
	Reload = 2.f;
	AmmoMax = 20.f;
	Ammo = AmmoMax;
	ProjectileSpeed = 6000.f;
	ConstructShotVectors();
	ChainDistance = 1000;
}

void AGrapplingHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGrapplingHook::ConstructShotVectors()
{
	ShotVectors.Add(FVector(ChainDistance, 0.f, 0.f));
}

FVector AGrapplingHook::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator AGrapplingHook::GetHipFireRotation()
{
	return HipFireRotation;
}

void AGrapplingHook::Fire()
{
	//Super::Fire();
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Fire was called"), Time);
	for (FVector Shot : ShotVectors)
	{
		FVector* StartTrace = new FVector(Muzzle->GetComponentLocation());
		FVector * EndTrace = new FVector(*StartTrace + FVector(Muzzle->GetComponentRotation().RotateVector(Shot)));
		FHitResult* HitResult = new FHitResult();
		FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
		TraceParams->AddIgnoredActor(Shooter);	// Ignore the Shooter when doing the trace (can't shoot yourself)
		DrawDebugVisuals();

		// If firing a round, do a line trace in front of the gun, check if there is a hit, and check if that hit is an actor
		if (GetWorld()->LineTraceSingleByChannel(*HitResult, *StartTrace, *EndTrace, ECC_Visibility, *TraceParams) && HitResult)
		{
			Logger::Log("Grappling hook hit something");
		}
		else
		{
			Logger::Log("Line trace failed");
		}

		delete HitResult;
		delete TraceParams;
		delete StartTrace;
		delete EndTrace;
	}	
}


