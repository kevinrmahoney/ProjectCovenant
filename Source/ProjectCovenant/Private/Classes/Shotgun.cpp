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
	Damage = 50.f;
	Range = 20000.f;
	Cooldown = 2.f;
	Falloff = 1.f; //not yet implemented, less damage depending on distance. 1 = 100%
	//TODO lower ammo count, but don't disable shooting with negative ammo yet
	Ammo = 100.f; //not yet implemented 
	TimeSinceLastShot = Cooldown;
}

void AShotgun::Tick(float DeltaTime) 
{
	TimeSinceLastShot = FMath::Min(TimeSinceLastShot + DeltaTime, Cooldown);

	if (Trigger)
	{
		Shoot();
	}
}

void AShotgun::SetShooter(ASubjectZero * NewShooter)
{
	Shooter = NewShooter;
}

void AShotgun::SetTrigger(bool T)
{
	Trigger = T;
}

void AShotgun::Shoot()
{
	bool DoDamage = false;
	FVector * StartTrace = new FVector(Muzzle->GetComponentLocation());
	FVector ForwardVector = Muzzle->GetForwardVector();
	FVector * EndTrace = new FVector(*StartTrace + (ForwardVector * Range));
	FRotator * Roll = new FRotator(Muzzle->GetComponentRotation());
	Roll->Roll += 360.f / RollCount;
	UWorld * World = GetWorld();
	DrawDebugLine(World, *StartTrace, *EndTrace, FColor::Green, false, 1110.f);
	
	EndTrace = new FVector(Muzzle->GetForwardVector()- Muzzle->GetComponentLocation());
	FRotator * Rotation = new FRotator(100.f, 0.f, 0.f);
	//*EndTrace = Rotation->RotateVector(ForwardVector);
	*EndTrace = Muzzle->GetComponentRotation().RotateVector(FVector(-Range, 0.f, 0.f));
	//*EndTrace *= Range;
	*EndTrace += *StartTrace;
	DrawDebugLine(World, *StartTrace, *EndTrace, FColor::Red, false, 1110.f);
	
	
	//for loop for radius of circle and nested for loop for roll
	for (int i = 1; i <= CircleCount; i++) 
	{	
	
		for (int j = 0; j < RollCount; j++) 
		{
			
		}
	}

	// See if cooldown has passed (while loop prevents shots from being buffered if frame rate is horrendous)
	if (TimeSinceLastShot >= Cooldown)
	{
		TimeSinceLastShot = TimeSinceLastShot - Cooldown;
		DoDamage = true;
	}

	if (DoDamage)
	{
		FHitResult * HitResult = new FHitResult();
		FCollisionQueryParams * TraceParams = new FCollisionQueryParams();
		TraceParams->AddIgnoredActor(Shooter);	// Ignore the Shooter when doing the trace (can't shoot yourself)

		// If firing a round, do a line trace in front of the gun, check if there is a hit, and check if that hit is an actor
		if (GetWorld()->LineTraceSingleByChannel(*HitResult, *StartTrace, *EndTrace, ECC_Pawn, *TraceParams) && HitResult && HitResult->GetActor())
		{
			// Calculate the end of the trace (the actor's hitbox)
			EndTrace = new FVector(*StartTrace + (HitResult->Distance * ForwardVector));

			// Get the victim and attempt to cast to SubjectZero
			ASubjectZero * Victim = Cast<ASubjectZero>(HitResult->GetActor());
			if (Victim && Shooter->HasAuthority())
			{
				DealDamage(Victim);
			}
		}
		delete HitResult;
		delete TraceParams;

		DrawLaser(StartTrace, EndTrace, 2.f);
		//PlayShootSound();
	}
	delete StartTrace;
	delete EndTrace;
	
}

void AShotgun::DealDamage(ASubjectZero * Victim)
{
	bool Killed = Victim->ReceiveDamage(Damage);
	Shooter->AddDamageDealt(Damage);

	if (Killed)
	{
		Shooter->AddKill();
		Logger::Log(Shooter->GetPlayerName().ToString() + " has killed " + Victim->GetPlayerName().ToString());
	}
}

void AShotgun::DrawLaser(FVector * Begin, FVector * End, float Duration)
{

}


