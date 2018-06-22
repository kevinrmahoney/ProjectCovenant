// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Shotgun.h"
#include "ItemWeapon.h"
#include "SubjectZero.h"

AShotgun::AShotgun()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 100.f;
	Range = 20000.f;
	Cooldown = 1.f;
	ReloadTime = 2.f;
	FallOff = 1.f;
	AmmoMax = 6.f;
	Ammo = AmmoMax;
	Damage = Damage / ShotVectors.Num();
}

// Called when the game starts or when spawned
void AShotgun::BeginPlay() 
{
	Super::BeginPlay();
}

void AShotgun::Tick(float DeltaTime) 
{
	Super::Super::Tick(DeltaTime);
	TimeSinceLastShot += DeltaTime;

	if(TimeSinceReload > 0.f)
	{
		TimeSinceReload = FMath::Max(TimeSinceReload - DeltaTime, 0.f);
		if(TimeSinceReload == 0.f)
		{
			Ammo = AmmoMax;
		}
	}
	else
	{
		Update();
	}
}

void AShotgun::Update()
{
	if(Ammo > 0)
	{
		// If the trigger is pulled
		if(Trigger)
		{
			// If the cooldown has passed
			if(TimeSinceLastShot > Cooldown)
			{
				Ammo--;
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
			}
		}
	}
}

void AShotgun::ConstructShotVectors()
{
	for(int i = 1; i <= CircleCount; i++)
	{
		FVector SpreadVector;
		for(int j = 0; j < RollCount; j++)
		{
			SpreadVector = FVector(Range, MaxConeAngle / i, 0.f);
			SpreadVector = SpreadVector.RotateAngleAxis(360 / RollCount * j, FVector(1.f, 0.f, 0.f));
			ShotVectors.Add(SpreadVector);
		}
	}
}

void AShotgun::Shoot()
{
	DrawDebugVisuals();
	PlayShootSound();

	if(HasAuthority())
	{
		float TotalDamage = 0.f;
		int count = 0;

		ASubjectZero * Victim = nullptr;

		//for loop for radius of circle and nested for loop for roll
		for(FVector Shot : ShotVectors)
		{
			FVector * StartTrace = new FVector(Muzzle->GetComponentLocation());	//start trace at the muzzle of the weapon (in world space)
			FVector * SpreadEnd = new FVector(0.f, 0.f, 0.f);
			FHitResult * HitResult = nullptr;
			FCollisionQueryParams * TraceParams = nullptr;

			*SpreadEnd = FVector(*StartTrace + FVector(Muzzle->GetComponentRotation().RotateVector(Shot)));

			HitResult = new FHitResult();
			TraceParams = new FCollisionQueryParams();
			TraceParams->AddIgnoredActor(Shooter);	// Ignore the Shooter when doing the trace (can't shoot yourself)

			// If firing a round, do a line trace in front of the gun, check if there is a hit, and check if that hit is an actor
			if(GetWorld()->LineTraceSingleByChannel(*HitResult, *StartTrace, *SpreadEnd, ECC_Pawn, *TraceParams) && HitResult && HitResult->GetActor())
			{
				if(!Victim)
				{
					Victim = Cast<ASubjectZero>(HitResult->GetActor());
				}

				count++;
				TotalDamage += Damage;
			}

			delete HitResult;
			delete TraceParams;
			delete StartTrace;
			delete SpreadEnd;
		}

		if(Victim)
		{
			DealDamage(Victim, TotalDamage);
		}
	}
}

void AShotgun::DealDamage(ASubjectZero * Victim, float TotalDamage)
{
	Super::DealDamage(Victim, TotalDamage);
}

FVector AShotgun::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator AShotgun::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector AShotgun::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator AShotgun::GetHipFireRotation()
{
	return HipFireRotation;
}