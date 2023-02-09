// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "GrapplingHook.h"
#include "SubjectZero.h"

AGrapplingHook::AGrapplingHook()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 20.f;
	FireRate = 3.0f;
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

	if (HasFired)
	{
		if (IsLatched)
			Grapple(DeltaTime);
	}
	else
		IsLatched = false;

	HasFired = false;
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

bool AGrapplingHook::CanFire()
{
	if (IsLatched)
		return true;
	else
		return Super::CanFire();
}

void AGrapplingHook::Fire()
{
	Super::Fire();
	//FireRateProgress = 0.f; //TODO
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Fire was called"), Time);

	HasFired = true;

	if (!IsLatched)
	{
		for (FVector Shot : ShotVectors)
		{
			FVector StartTrace = FVector(Muzzle->GetComponentLocation());
			FVector EndTrace = FVector(StartTrace + FVector(Muzzle->GetComponentRotation().RotateVector(Shot)));
			FHitResult HitResult = FHitResult();
			FCollisionQueryParams TraceParams = FCollisionQueryParams();
			TraceParams.AddIgnoredActor(Shooter);	// Ignore the Shooter when doing the trace (can't shoot yourself)
			//DrawDebugVisuals();

			// If firing a round, do a line trace in front of the gun, check if there is a hit, and check if that hit is an actor
			if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, TraceParams) && HitResult.bBlockingHit)
			{
				TargetLocation = HitResult.Location;
				IsLatched = true;
				Logger::Log("Grappling hook hit something");
			}
			else
			{
				Logger::Log("Line trace failed");
			}
		}
	}

	Ammo = 0;
}

void AGrapplingHook::Grapple(float DeltaTime)
{
	GrappleTime += DeltaTime;
	Logger::Log(TEXT("Getting closer..."));

	FVector DistanceToTarget = TargetLocation - Shooter->GetActorLocation();
	if (DistanceToTarget.Size() > GrappleCutoffDistance)
	{
		//Shooter->GetCharacterMovement()->GravityScale = 0.f;
		//Shooter->GetMesh()->SetEnableGravity(false);
		//Shooter->bSimGravityDisabled = true;
		//Shooter->GetCapsuleComponent()->SetEnableGravity(false);
		Shooter->GetCharacterMovement()->AddForce(DistanceToTarget.GetSafeNormal() * MaxDistancePerSecond * 100.f);

		DrawDebugLine(GetWorld(), Muzzle->GetComponentLocation(), TargetLocation, FColor::Black, false, -1.f, 0U, 10.f);
	}

}
