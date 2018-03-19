// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HitscanWeapon.h"
#include "BasePlayerState.h"
#include "SubjectZero.h"
#include "HumanController.h"
#include "UnrealNetwork.h"
#include "ItemWeapon.h"
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
	ConstructShotVectors();
}

// Called every frame
void AHitscanWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeSinceLastShot += DeltaTime;
	Update();
}

void AHitscanWeapon::SetItem(UItemWeapon * NewItem)
{
	if(Role == ROLE_Authority || Role == ROLE_AutonomousProxy)
	{
		Item = NewItem;
		TimeSinceLastShot = UGameplayStatics::GetRealTimeSeconds(GetWorld()) - Item->LastShotTimeStamp;
	}
}

void AHitscanWeapon::Update()
{
	// If the trigger is pulled
	if(Trigger)
	{
		// If the cooldown has passed
		if(TimeSinceLastShot > Cooldown)
		{
			// Shoot the weapon
			Shoot();

			// Subtract the cooldown from the time passed since the last shot.
			// make sure the outcome does not go above value of Cooldown
			TimeSinceLastShot = 0.f;
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
	DrawVisuals();
	PlayShootSound();
}

void AHitscanWeapon::ConstructShotVectors()
{
	ShotVectors.Add(FVector(Range, 0.f, 0.f));
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
	//DrawDebugVisuals(); TODO: enable with console command

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
		// TODO: Victim isn't deleted, causes game to crash when you do
		// This is a potential memory leak?
		//delete Victim;
	}
}

void AHitscanWeapon::DrawDebugVisuals()
{
	FVector StartPoint = FVector(Muzzle->GetComponentLocation());
	FVector EndPoint;
	for(FVector V : ShotVectors)
	{
		EndPoint = StartPoint + FVector(Muzzle->GetComponentRotation().RotateVector(V));
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, Cooldown);
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

FVector AHitscanWeapon::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator AHitscanWeapon::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector AHitscanWeapon::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator AHitscanWeapon::GetHipFireRotation()
{
	return HipFireRotation;
}
