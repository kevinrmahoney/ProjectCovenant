// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Railgun.h"
#include "SubjectZero.h"

// Sets default values
ARailgun::ARailgun()
{
	float Damage = 100.f;
	float Range = 20000.f;
	float Cooldown = 3.f;
	float Falloff = 1.f;
	float Ammo = 100.f;
}

// Called when the game starts or when spawned
void ARailgun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARailgun::Tick(float DeltaTime)
{
	TimeSinceLastShot = TimeSinceLastShot + DeltaTime;

	Logger::Log(FString::SanitizeFloat(TimeSinceLastShot));

	if(Trigger)
	{
		Shoot();
	}
}

void ARailgun::SetShooter(ASubjectZero * NewShooter)
{
	Shooter = NewShooter;
}

void ARailgun::SetTrigger(bool T)
{
	Trigger = T;
}

void ARailgun::Shoot()
{
	bool DoDamage = false;
	FVector * StartTrace = new FVector(Muzzle->GetComponentLocation());
	FVector ForwardVector = Muzzle->GetForwardVector();
	FVector * EndTrace = new FVector(*StartTrace + (ForwardVector * Range));

	// See if cooldown has passed (while loop prevents shots from being buffered if frame rate is horrendous)
	while(TimeSinceLastShot >= Cooldown)
	{
		TimeSinceLastShot = TimeSinceLastShot - Cooldown;
		DoDamage = true;
	}

	if(DoDamage)
	{
		FHitResult* HitResult = new FHitResult();
		FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
		TraceParams->AddIgnoredActor(Shooter);	// Ignore the Shooter when doing the trace (can't shoot yourself)

												// If firing a round, do a line trace in front of the gun, check if there is a hit, and check if that hit is an actor
		if(GetWorld()->LineTraceSingleByChannel(*HitResult, *StartTrace, *EndTrace, ECC_Pawn, *TraceParams) && HitResult && HitResult->GetActor())
		{
			// Calculate the end of the trace (the actor's hitbox)
			EndTrace = new FVector(*StartTrace + (HitResult->Distance * ForwardVector));

			// Get the victim and attempt to cast to SubjectZero
			ASubjectZero * Victim = Cast<ASubjectZero>(HitResult->GetActor());
			if(Victim && Shooter->HasAuthority())
			{
				DealDamage(Victim);
			}
		}

		delete HitResult;
		delete TraceParams;

	}
	DrawLaser(StartTrace, EndTrace, 2.f);
	delete StartTrace;
	delete EndTrace;
}

void ARailgun::DealDamage(ASubjectZero * Victim)
{
	bool Killed = Victim->ReceiveDamage(Damage);
	Shooter->AddDamageDealt(Damage);

	if(Killed)
	{
		Shooter->AddKill();
		Logger::Log(Shooter->GetPlayerName().ToString() + " has killed " + Victim->GetPlayerName().ToString());
	}
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