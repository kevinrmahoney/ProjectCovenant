// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HitscanWeapon.h"
#include "SubjectZero.h"

// Sets default values
AHitscanWeapon::AHitscanWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
		while(TimeSinceLastShot >= Cooldown)
		{
			TimeSinceLastShot = TimeSinceLastShot - Cooldown;
			Fire = true;
		}

		if(Fire)
		{
			Shoot(DeltaTime);
		}
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

void AHitscanWeapon::Shoot(float DeltaTime)
{
	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = Muzzle->GetComponentLocation();
	FVector ForwardVector = Muzzle->GetForwardVector();
	FVector EndTrace = StartTrace + (ForwardVector * Range);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(this);

	if(GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Pawn, *TraceParams))
	{
		if(HitResult)
		{
			if(HitResult->GetActor())
			{
				DrawDebugLine(GetWorld(), StartTrace, StartTrace + (HitResult->Distance * ForwardVector), FColor::Red, false, Cooldown);

				ASubjectZero * Victim = Cast<ASubjectZero>(HitResult->GetActor());
				if(Victim && HasAuthority())
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
			else
			{
				DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, Cooldown);
			}

		}
		else
		{
			DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, Cooldown);
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, Cooldown);
	}

	delete HitResult;
	delete TraceParams;
}