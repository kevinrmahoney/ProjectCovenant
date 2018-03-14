// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Shotgun.h"
#include "SubjectZero.h"

AShotgun::AShotgun()
{
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
	Spread.Add(FVector(Range, 0.f, 0.f));
	for(int i = 1; i <= CircleCount; i++)
	{
		FVector SpreadVector;
		for(int j = 0; j < RollCount; j++)
		{
			SpreadVector = FVector(Range, MaxConeAngle / i, 0.f);
			SpreadVector = SpreadVector.RotateAngleAxis(360 / RollCount * j, FVector(1.f, 0.f, 0.f));
			Spread.Add(SpreadVector);
		}
	}
}

void AShotgun::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
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
	// See if cooldown has passed (while loop prevents shots from being buffered if frame rate is horrendous)
	int count = 0;
	bool DoDamage = false;

	while(TimeSinceLastShot >= Cooldown)
	{
		TimeSinceLastShot = TimeSinceLastShot - Cooldown;
		DoDamage = true;
	}

	if(DoDamage)
	{

		DrawLaser();
		PlayShootSound();

		if(HasAuthority())
		{
			float TotalDamage = 0.f;

			FVector * StartTrace = new FVector(Muzzle->GetComponentLocation());	//start trace at the muzzle of the weapon (in world space)
			FVector * AxisEnd = new FVector(*StartTrace + (Muzzle->GetForwardVector() * Range)); //because the forwardvector comes from the origin, add it to the start trace
			FVector * SpreadEnd = new FVector(0.f, 0.f, 0.f);
			FRotator * Rotation = new FRotator(0.f, 0.f, 0.f);
			ASubjectZero * Victim = nullptr;
			FHitResult * HitResult = nullptr;
			FCollisionQueryParams * TraceParams = nullptr;

			//for loop for radius of circle and nested for loop for roll
			for(FVector V : Spread)
			{
				V = FVector(Muzzle->GetComponentRotation().RotateVector(V));
				*SpreadEnd = FVector(*StartTrace + V);

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

					if(Shooter && Shooter->HasAuthority())
					{
						count++;
						TotalDamage += Damage;
					}
				}
			}
			delete HitResult;
			delete TraceParams;
			delete StartTrace;
			delete AxisEnd;

			if(Victim)
			{
				DealDamage(Victim, TotalDamage);
			}
		}
	}
}

void AShotgun::DealDamage(ASubjectZero * Victim, float TotalDamage)
{
	Super::DealDamage(Victim, TotalDamage);
}

void AShotgun::DrawLaser()
{
	FVector StartPoint = FVector(Muzzle->GetComponentLocation());
	FVector EndPoint;
	for(FVector V : Spread)
	{
		EndPoint = StartPoint + FVector(Muzzle->GetComponentRotation().RotateVector(V));
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Orange, false, .1f);
	}
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