// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Railgun.h"
#include "BasePlayerState.h"
#include "SubjectZero.h"



// Sets default values
ARailgun::ARailgun()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARailgun::BeginPlay()
{
	Super::BeginPlay();
	Damage = 100.f;
	Range = 20000.f;
	Cooldown = 2.25f;
	Falloff = 1.f;
	Ammo = 100.f;
	Duration = 2.f;
}

// Called every frame
void ARailgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARailgun::Update()
{
	// If the trigger is pulled
	if(Trigger)
	{
		// If the cooldown has passed
		if(TimeSinceLastShot > Cooldown)
		{
			// Shoot the weapon
			Shoot();

			// Subtract the cooldown from the time passed since the last shot.
			// make sure the outcome does not go above value of Cooldown
			while(TimeSinceLastShot > Cooldown) TimeSinceLastShot -= Cooldown;
		}
	}
}

void ARailgun::ConstructShotVectors()
{
	ShotVectors.Add(FVector(Range, 0.f, 0.f));
}

void ARailgun::SetShooter(ASubjectZero * NewShooter)
{
	Super::SetShooter(NewShooter);
}

void ARailgun::SetTrigger(bool T)
{
	Super::SetTrigger(T);
}

void ARailgun::Shoot()
{
	PlayShootSound();
	//DrawDebugVisuals(); TODO: enable with console command
	DrawVisuals();

	if(HasAuthority())
	{
		ASubjectZero * Victim = nullptr;

		for(FVector Shot : ShotVectors)
		{
			FVector * StartTrace = new FVector(Muzzle->GetComponentLocation());
			FVector * EndTrace = new FVector(*StartTrace + FVector(Muzzle->GetComponentRotation().RotateVector(Shot)));
			FHitResult * HitResult = new FHitResult();
			FCollisionQueryParams * TraceParams = new FCollisionQueryParams();
			TraceParams->AddIgnoredActor(Shooter);	// Ignore the Shooter when doing the trace (can't shoot yourself)

			// If firing a round, do a line trace in front of the gun, check if there is a hit, and check if that hit is an actor
			if(GetWorld()->LineTraceSingleByChannel(*HitResult, *StartTrace, *EndTrace, ECC_Pawn, *TraceParams) && HitResult && HitResult->GetActor())
			{
				// Get the victim and attempt to cast to SubjectZero
				Victim = Cast<ASubjectZero>(HitResult->GetActor());
				if(Victim)
				{
					DealDamage(Victim, Damage);
				}
			}

			delete HitResult;
			delete TraceParams;
			delete StartTrace;
			delete EndTrace;
		}
		//delete Victim;
	}
}

void ARailgun::DealDamage(ASubjectZero * Victim, float TotalDamage)
{
	Super::DealDamage(Victim, TotalDamage);
}

FVector ARailgun::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator ARailgun::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector ARailgun::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator ARailgun::GetHipFireRotation()
{
	return HipFireRotation;
}