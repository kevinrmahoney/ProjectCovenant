// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HitscanWeapon.h"
#include "SubjectZero.h"

// Sets default values
AHitscanWeapon::AHitscanWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"), false);
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Mesh->SetVisibility(true);
	Mesh->SetOnlyOwnerSee(false);
	Mesh->SetOwnerNoSee(false);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"), false);
	Muzzle->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
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

	TimeSinceLastShot = TimeSinceLastShot + DeltaTime;

	if(Trigger)
	{
		Shoot();
	}
}

void AHitscanWeapon::SetShooter(ASubjectZero * NewShooter)
{
	Shooter = NewShooter;
}

void AHitscanWeapon::SetTrigger(bool T)
{
	Trigger = T;
}

void AHitscanWeapon::Shoot()
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

	DrawLaser(StartTrace, EndTrace, GetWorld()->DeltaTimeSeconds * 2.f);

	delete StartTrace; 
	delete EndTrace;
}

void AHitscanWeapon::DealDamage(ASubjectZero * Victim)
{
	bool Killed = Victim->ReceiveDamage(Damage);
	Shooter->AddDamageDealt(Damage);

	if(Killed)
	{
		Shooter->AddKill();
		Logger::Log(Shooter->GetPlayerName().ToString() + " has killed " + Victim->GetPlayerName().ToString());
	}
}

void AHitscanWeapon::DrawLaser(FVector * Begin, FVector * End, float Duration)
{
	UWorld * World = GetWorld();

	DrawDebugLine(World, *Begin, *End, FColor::Green, false, Duration);
	DrawDebugLine(World, *Begin + FVector(0.2f, 0.f, 0.f), *End, FColor::Green, false, Duration);
	DrawDebugLine(World, *Begin + FVector(0.f, 0.f, 0.2f), *End, FColor::Green, false, Duration);
	DrawDebugLine(World, *Begin + FVector(-0.2f, 0.f, 0.f), *End, FColor::Green, false, Duration);
	DrawDebugLine(World, *Begin + FVector(0.f, 0.f, -0.2f), *End, FColor::Green, false, Duration);
}