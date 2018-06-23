// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "LightningGun.h"
#include "BasePlayerState.h"
#include "SubjectZero.h"
#include "HumanController.h"
#include "ItemWeapon.h"
#include "BaseMode.h"

// Sets default values
ALightningGun::ALightningGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 10.f;
	Range = 20000.f;
	FireRate = 0.1f;
	Reload = 4.f;
	FallOff = 1.f;
	AmmoMax = 30.f;
	Ammo = AmmoMax;
}

// Called when the game starts or when spawned
void ALightningGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALightningGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FireRateProgress += DeltaTime;

	if(Trigger && Ammo > 0.f)
	{
		if(ReloadProgress >= Reload)
		{
			ReloadProgress = Reload + 1.f;
			Ammo = 0.f;
		}
	}
	else
	{
		ReloadProgress = FMath::Max(ReloadProgress - DeltaTime, 0.f);
		if(ReloadProgress < Reload)
		{
			Ammo = AmmoMax;
		}
	}
	Update(DeltaTime);
}

void ALightningGun::Update(float DeltaTime)
{
	if(Ammo > 0)
	{
		if(FireRateProgress > 0.f)
		{
			// If the trigger is pulled
			if(Trigger)
			{
				// If the cooldown has passed
				if(FireRateProgress > FireRate)
				{
					ReloadProgress = ReloadProgress + FireRate;
					// Shoot the weapon
					Shoot();
					if(RecoilComponent)
					{
						RecoilComponent->Recoil();
					}

					// Subtract the cooldown from the time passed since the last shot.
					// make sure the outcome does not go above value of Cooldown
					FireRateProgress = 0.f;
					//Item->LastShotTimeStamp = 0.f;
					if(Item && (Role == ROLE_Authority || Role == ROLE_AutonomousProxy))
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
	DrawVisuals();
	PlayShootSound();
}

void ALightningGun::ConstructShotVectors()
{
	ShotVectors.Add(FVector(Range, 0.f, 0.f));
}

void ALightningGun::Shoot()
{
	if(HasAuthority())
	{
		ASubjectZero * Victim = nullptr;

		//for loop for radius of circle and nested for loop for roll
		for(FVector Shot : ShotVectors)
		{
			FVector * StartTrace = new FVector(Muzzle->GetComponentLocation());
			FVector * EndTrace = new FVector(*StartTrace + FVector(Muzzle->GetComponentRotation().RotateVector(Shot)));
			FHitResult* HitResult = new FHitResult();
			FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
			TraceParams->AddIgnoredActor(Shooter);	// Ignore the Shooter when doing the trace (can't shoot yourself)

													// If firing a round, do a line trace in front of the gun, check if there is a hit, and check if that hit is an actor
			if(GetWorld()->LineTraceSingleByChannel(*HitResult, *StartTrace, *EndTrace, ECC_Pawn, *TraceParams) && HitResult && HitResult->GetActor())
			{
				// Get the victim and attempt to cast to SubjectZero
				Victim = Cast<ASubjectZero>(HitResult->GetActor());
				if(Victim && Shooter && Shooter->HasAuthority())
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

void ALightningGun::DealDamage(ASubjectZero * Victim, float TotalDamage)
{
	Super::DealDamage(Victim, TotalDamage);
}

FVector ALightningGun::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator ALightningGun::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector ALightningGun::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator ALightningGun::GetHipFireRotation()
{
	return HipFireRotation;
}
