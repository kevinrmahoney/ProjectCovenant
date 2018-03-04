// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HitscanWeapon.h"
#include "BasePlayerState.h"
#include "SubjectZero.h"
#include "HumanController.h"
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
				DealDamage(Victim, Damage);
			}
		}

		delete HitResult;
		delete TraceParams;
	}

	DrawLaser(StartTrace, EndTrace, GetWorld()->DeltaTimeSeconds * 2.f);

	delete StartTrace; 
	delete EndTrace;
}

void AHitscanWeapon::DealDamage(ASubjectZero * Victim, float TotalDamage)
{
	// Only execute the following code on the server
	if(HasAuthority())
	{
		// Deal damage to the victim, returns if the player was killed by the damage
		bool Killed = Victim->ReceiveDamage(TotalDamage);

		// Log the damage and if the player was killed by it
		Logger::Log(Shooter->GetPlayerName().ToString() + " has dealt " + FString::SanitizeFloat(TotalDamage) + " to " + Victim->GetPlayerName().ToString() + " using " + GetName());
		if(Killed) Logger::Log(Shooter->GetPlayerName().ToString() + " has killed " + Victim->GetPlayerName().ToString() + " using " + GetName());

		// Obtain the player states for the shooter and the victim
		ABasePlayerState * ShooterPlayerState = Cast<ABasePlayerState>(Shooter->PlayerState);
		ABasePlayerState * VictimPlayerState = Cast<ABasePlayerState>(Victim->PlayerState);

		// If the player state is successfully obtained, add the damage that was dealt to the player state, and if killed, add the kill
		if(ShooterPlayerState)
		{
			ShooterPlayerState->AddDamageDealt(TotalDamage);
			if(Killed) ShooterPlayerState->AddKill(1);
		}
		else
		{
			Logger::Error("Could not cast or obtain shooter's PlayerState");
		}

		// If the player state is successfully obtained, add the damage that was dealt to the player state, and if killed, add the kill
		if(VictimPlayerState)
		{
			VictimPlayerState->AddDamageTaken(TotalDamage);
			if(Killed) VictimPlayerState->AddDeath(1);
		}
		else
		{
			Logger::Error("Could not cast or obtain victim's PlayerState");
		}

		if(Killed)
		{
			if(ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode()))
			{
				if(AHumanController * HumanController = Cast<AHumanController>(Victim->GetController()))
				{
					Mode->KillPlayer(HumanController);
				}
			}
		}
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