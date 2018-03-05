// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HitscanWeapon.h"
#include "BasePlayerState.h"
#include "SubjectZero.h"
#include "HumanController.h"
#include "UnrealNetwork.h"
#include "BaseMode.h"

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

void AHitscanWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	// The follow variables are replicated from server to the clients
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHitscanWeapon, Trigger)
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

	TimeSinceLastShot = FMath::Min(TimeSinceLastShot + DeltaTime, Cooldown);

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
	while(TimeSinceLastShot >= Cooldown)
	{
		TimeSinceLastShot = TimeSinceLastShot - Cooldown;
		DoDamage = true;
	}
	
	if(DoDamage)
	{
		DrawLaser();
		if(HasAuthority())
		{
			FVector * StartTrace = new FVector(Muzzle->GetComponentLocation());
			FVector ForwardVector = Muzzle->GetForwardVector();
			FVector * EndTrace = new FVector(*StartTrace + (ForwardVector * Range));
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

void AHitscanWeapon::DealDamage(ASubjectZero * Victim, float TotalDamage)
{
	ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode());
	if(Mode)
	{
		Mode->DealDamage(Shooter, Victim, TotalDamage, this);
	}
}

void AHitscanWeapon::DrawLaser()
{
	UWorld * World = GetWorld();

	FVector StartTrace = FVector(Muzzle->GetComponentLocation());
	FVector ForwardVector = Muzzle->GetForwardVector();
	FVector EndTrace = FVector(StartTrace + (ForwardVector * Range));

	DrawDebugLine(World, StartTrace, EndTrace, FColor::Green, false, Duration);
	DrawDebugLine(World, StartTrace + FVector(0.2f, 0.f, 0.f), EndTrace, FColor::Green, false, Duration);
	DrawDebugLine(World, StartTrace + FVector(0.f, 0.f, 0.2f), EndTrace, FColor::Green, false, Duration);
	DrawDebugLine(World, StartTrace + FVector(-0.2f, 0.f, 0.f), EndTrace, FColor::Green, false, Duration);
	DrawDebugLine(World, StartTrace + FVector(0.f, 0.f, -0.2f), EndTrace, FColor::Green, false, Duration);
}

FVector AHitscanWeapon::GetAimDownSightsLocation()
{
	return HipfireLocation;
}

FRotator AHitscanWeapon::GetAimDownSightsRotation()
{
	return HipfireRotation;
}