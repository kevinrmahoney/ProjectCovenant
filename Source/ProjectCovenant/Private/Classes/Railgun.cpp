// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Railgun.h"
#include "BasePlayerState.h"
#include "ItemWeapon.h"
#include "SubjectZero.h"

// Sets default values
ARailgun::ARailgun()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 100.f;
	Range = 20000.f;
	Cooldown = 2.f;
	ReloadTime = 2.f;
	FallOff = 1.f;
	AmmoMax = 1.f;
	Ammo = AmmoMax;
}

// Called when the game starts or when spawned
void ARailgun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARailgun::Tick(float DeltaTime)
{
	Super::Super::Tick(DeltaTime);
	TimeSinceLastShot += DeltaTime;

	if(Trigger && Ammo > 0.f)
	{
		if(TimeSinceReload >= ReloadTime)
		{
			TimeSinceReload = ReloadTime * 2.f;
			Ammo = 0.f;
		}
		Update();
	}
	else
	{
		TimeSinceReload = FMath::Max(TimeSinceReload - DeltaTime, 0.f);
		if(TimeSinceReload == 0.f)
		{
			Ammo = 1.f;
		}
	}
}

void ARailgun::Update()
{
	if(Ammo > 0)
	{
		// If the trigger is pulled
		if(Trigger)
		{
			// If the cooldown has passed
			if(TimeSinceLastShot > Cooldown)
			{
				TimeSinceReload = TimeSinceReload + Cooldown;

				Ammo = 0.f;
				// Shoot the weapon
				Shoot();
				if(RecoilComponent)
				{
					RecoilComponent->Recoil();
				}

				// Subtract the cooldown from the time passed since the last shot.
				// make sure the outcome does not go above value of Cooldown
				TimeSinceLastShot = 0.f;
				if(Item)
				{
					Item->SetLastShotTimeStamp(GetWorld());
				}
				else
				{
					Logger::Log("Could not find Item when attempting to set last shot time stamp");
				}
			}
		}
	}
}

void ARailgun::ConstructShotVectors()
{
	ShotVectors.Add(FVector(Range, 0.f, 0.f));
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