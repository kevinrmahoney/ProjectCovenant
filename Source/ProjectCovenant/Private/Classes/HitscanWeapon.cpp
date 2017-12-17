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
	
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"), false);
	GunMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	GunMesh->SetVisibility(true);
	GunMesh->SetOnlyOwnerSee(false);
	GunMesh->SetOwnerNoSee(false);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"), false);
	Muzzle->AttachToComponent(GunMesh, FAttachmentTransformRules::KeepRelativeTransform);
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
		// See if cooldown has passed (while loop prevents shots from being buffered if frame rate is horrendous)
		while(TimeSinceLastShot >= Cooldown)
		{
			TimeSinceLastShot = TimeSinceLastShot - Cooldown;
			Fire = true;
		}

		FHitResult* HitResult = new FHitResult();
		FVector StartTrace = Muzzle->GetComponentLocation();
		FVector ForwardVector = Muzzle->GetForwardVector();
		FVector EndTrace = StartTrace + (ForwardVector * Range);
		FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
		TraceParams->AddIgnoredActor(Shooter);	// Ignore the Shooter when doing the trace (can't shoot yourself)

		// If firing a round, do a line trace in front of the gun, check if there is a hit, and check if that hit is an actor
		if(Fire && GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Pawn, *TraceParams) && HitResult && HitResult->GetActor())
		{
			// Calculate the end of the trace (the actor's hitbox)
			EndTrace = StartTrace + (HitResult->Distance * ForwardVector);

			// Get the victim and attempt to cast to SubjectZero
			ASubjectZero * Victim = Cast<ASubjectZero>(HitResult->GetActor());
			if(Victim && Shooter->HasAuthority())
			{
				bool Killed = Victim->ReceiveDamage(Damage);
				Shooter->AddDamageDealt(Damage);

				if(Killed)
				{
					Shooter->AddKill();
					Logger::Log(Shooter->GetPlayerName().ToString() + " has killed " + Victim->GetPlayerName().ToString());
				}
			}
		}

		delete HitResult;
		delete TraceParams;

		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, DeltaTime * 2.f);
		DrawDebugLine(GetWorld(), StartTrace + FVector(0.2f, 0.f, 0.f), EndTrace, FColor::Red, false, DeltaTime * 2.f);
		DrawDebugLine(GetWorld(), StartTrace + FVector(0.f, 0.f, 0.2f), EndTrace, FColor::Red, false, DeltaTime * 2.f);
		DrawDebugLine(GetWorld(), StartTrace + FVector(-0.2f, 0.f, 0.f), EndTrace, FColor::Red, false, DeltaTime * 2.f);
		DrawDebugLine(GetWorld(), StartTrace + FVector(0.f, 0.f, -0.2f), EndTrace, FColor::Red, false, DeltaTime * 2.f);

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