// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Railgun.h"
#include "BasePlayerState.h"
#include "SubjectZero.h"



// Sets default values
ARailgun::ARailgun()
{
}

// Called when the game starts or when spawned
void ARailgun::BeginPlay()
{
	Super::BeginPlay();
	Damage = 75.f;
	Range = 20000.f;
	Cooldown = 2.25f;
	Falloff = 1.f;
	Ammo = 100.f;
}

// Called every frame
void ARailgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	bool DoDamage = false;
	FVector * StartTrace = new FVector(Muzzle->GetComponentLocation());
	FVector ForwardVector = Muzzle->GetForwardVector();
	FVector * EndTrace = new FVector(*StartTrace + (ForwardVector * Range));

	// See if cooldown has passed (while loop prevents shots from being buffered if frame rate is horrendous)
	if(TimeSinceLastShot >= Cooldown)
	{
		TimeSinceLastShot = TimeSinceLastShot - Cooldown;
		DoDamage = true;
	}

	if(DoDamage)
	{
		FHitResult * HitResult = new FHitResult();
		FCollisionQueryParams * TraceParams = new FCollisionQueryParams();
		TraceParams->AddIgnoredActor(Shooter);	// Ignore the Shooter when doing the trace (can't shoot yourself)

		// If firing a round, do a line trace in front of the gun, check if there is a hit, and check if that hit is an actor
		if(GetWorld()->LineTraceSingleByChannel(*HitResult, *StartTrace, *EndTrace, ECC_Pawn, *TraceParams) && HitResult && HitResult->GetActor())
		{
			// Calculate the end of the trace (the actor's hitbox)
			EndTrace = new FVector(*StartTrace + (HitResult->Distance * ForwardVector));

			// Get the victim and attempt to cast to SubjectZero
			ASubjectZero * Victim = Cast<ASubjectZero>(HitResult->GetActor());
			if(Victim)
			{
				DealDamage(Victim, Damage);
			}
		}

		delete HitResult;
		delete TraceParams;

		DrawLaser(StartTrace, EndTrace, 2.f);
		PlayShootSound();
	}

	delete StartTrace;
	delete EndTrace;
}

void ARailgun::DealDamage(ASubjectZero * Victim, float TotalDamage)
{
	Super::DealDamage(Victim, TotalDamage);
}

void ARailgun::DrawLaser(FVector * Begin, FVector * End, float Duration)
{
	UWorld * World = GetWorld();

	DrawDebugLine(World, *Begin, *End, FColor::Red, false, Duration);
	DrawDebugLine(World, *Begin + FVector(0.2f, 0.f, 0.f), *End, FColor::Red, false, Duration);
	DrawDebugLine(World, *Begin + FVector(0.f, 0.f, 0.2f), *End, FColor::Red, false, Duration);
	DrawDebugLine(World, *Begin + FVector(-0.2f, 0.f, 0.f), *End, FColor::Red, false, Duration);
	DrawDebugLine(World, *Begin + FVector(0.f, 0.f, -0.2f), *End, FColor::Red, false, Duration);

}

FVector ARailgun::GetAimDownSightsLocation()
{
	return HipfireLocation;
}

FRotator ARailgun::GetAimDownSightsRotation()
{
	return HipfireRotation;
}