// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Shotgun.h"
#include "ItemWeapon.h"
#include "SubjectZero.h"

AShotgun::AShotgun()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShotgun::BeginPlay() 
{
	Super::BeginPlay();
	//TODO: adjust values for shotgun
	Damage = 100.f / (CircleCount * RollCount + 1);
	Range = 5000.f;
	Cooldown = 1.f;
	Falloff = 1.f; //not yet implemented, less damage depending on distance. 1 = 100%
	//TODO lower ammo count, but don't disable shooting with negative ammo yet
	Ammo = 100.f; //not yet implemented 
	Duration = 0.25;
	TimeSinceLastShot = Cooldown;
	ShotVectors.Add(FVector(Range, 0.f, 0.f));
}

void AShotgun::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
}

void AShotgun::Update()
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
			TimeSinceLastShot = 0.f;
			if(Item)
			{
				Item->SetLastShotTimeStamp(GetWorld());
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
	Logger::Log("Constructed shot vectors: " + FString::FromInt(ShotVectors.Num()));
}

void AShotgun::SetShooter(ASubjectZero * NewShooter)
{
	Super::SetShooter(NewShooter);
}

void AShotgun::SetTrigger(bool T)
{
	Super::SetTrigger(T);
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
		//delete Victim;
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