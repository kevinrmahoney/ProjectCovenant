// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HitscanWeapon.h"
#include "SubjectZero.h"
#include "Logger.h"

// Sets default values
AHitscanWeapon::AHitscanWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHitscanWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitscanWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool Fire = false;

	TimeSinceLastShot = TimeSinceLastShot + DeltaTime;

	if(Trigger)
	{
		while(TimeSinceLastShot >= TimeBetweenShot)
		{
			TimeSinceLastShot = TimeSinceLastShot - TimeBetweenShot;
			Fire = true;
		}
		
		if(Fire)
		{
			Shoot();
		}
	}
}

void AHitscanWeapon::SetTrigger(bool T)
{
	Trigger = T;
}

void AHitscanWeapon::Shoot()
{
	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = GetActorLocation() + FVector(0.f, 0.f, 0.f);
	FVector ForwardVector = GetActorForwardVector();
	FVector EndTrace = StartTrace + (ForwardVector * Range);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(this);

	if(GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Pawn, *TraceParams))
	{
		if(HitResult)
		{
			if((HitResult->GetActor()))
			{
				ASubjectZero * Victim = Cast<ASubjectZero>(HitResult->GetActor());
				if(Victim)
				{
					bool Killed = Victim->TakeDamage(Damage);
					if(Killed)
					{
						Logger::Log(Victim->GetName());
					}
				}
			}
		}
	}

	delete HitResult;
	delete TraceParams;
}