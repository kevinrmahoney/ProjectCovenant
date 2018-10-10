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
	Logger::Log(Shooter->GetCharacterMovement()->GravityScale);
	if (bIsGrappling)
	{
		Grapple(DeltaTime);
	}
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
	// check if player is grappling
	return !bIsGrappling && Super::CanFire();
}

void AGrapplingHook::Fire()
{
	Super::Fire();
	FireRateProgress = 0.f; //TODO
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
			TargetLocation = HitResult->Location;
			bIsGrappling = true;
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

void AGrapplingHook::Grapple(float DeltaTime)
{
	FVector DistanceToTarget = TargetLocation - Shooter->GetActorLocation();
	if (DistanceToTarget.Size() > GrappleCutoffDistance)
	{
		Shooter->GetCharacterMovement()->GravityScale = 0.f;
		//Shooter->GetMesh()->SetEnableGravity(false);
		//Shooter->bSimGravityDisabled = true;
		//Shooter->GetCapsuleComponent()->SetEnableGravity(false);
		Shooter->GetCharacterMovement()->MaxFlySpeed = 100000.f;
		Shooter->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Flying;
		Shooter->AddMovementInput(DistanceToTarget.GetSafeNormal() * MaxDistancePerSecond * DeltaTime);
		//Shooter->LaunchCharacter
		//(
		//	DistanceToTarget.GetSafeNormal() * 1000,
		//	false,
		//	false
		//);
	}
	else
	{
		bIsGrappling = false;
		
		//Shooter->GetMesh()->SetEnableGravity(true);
		//Shooter->bSimGravityDisabled = false;
		//Shooter->GetCapsuleComponent()->SetEnableGravity(true);
		//Shooter->GetCharacterMovement()->GravityScale = 1.0f;
		Shooter->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;
		
	}

}
