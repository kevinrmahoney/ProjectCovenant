// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "ItemWeapon.h"
#include "UnrealNetwork.h"
#include "SubjectZero.h"
#include "Weapon.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"), false);
	GunMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	GunMesh->SetVisibility(true);
	GunMesh->SetOnlyOwnerSee(false);
	GunMesh->SetOwnerNoSee(false);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"), false);
	Muzzle->AttachToComponent(GunMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	// The follow variables are replicated from server to the clients
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWeapon, Trigger)
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	ConstructShotVectors();
}

void AWeapon::ConstructShotVectors()
{
	ShotVectors.Add(FVector(Range, 0.f, 0.f));
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeSinceLastShot += DeltaTime;
	Update();
}

void AWeapon::Update()
{
	
}

void AWeapon::SetItem(UItemWeapon * NewItem)
{
	if(Role == ROLE_Authority || Role == ROLE_AutonomousProxy)
	{
		Item = NewItem;
		TimeSinceLastShot = FMath::Min(UGameplayStatics::GetRealTimeSeconds(GetWorld()) - Item->LastShotTimeStamp, Cooldown);
		TimeSinceLastShot = TimeSinceLastShot - WeaponSwitchCooldown;
		Logger::Chat("TWLS " + FString::SanitizeFloat(TimeSinceLastShot));
	}
}

void AWeapon::SetShooter(ASubjectZero * NewShooter)
{
	Shooter = NewShooter;
}

void AWeapon::SetTrigger(bool T)
{
	Trigger = T;
}

void AWeapon::Shoot()
{

}

void AWeapon::DealDamage(ASubjectZero * Victim, float TotalDamage)
{

}

void AWeapon::DrawDebugVisuals()
{
}

FVector AWeapon::GetAimDownSightsLocation()
{
	return AimDownSightsLocation;
}

FRotator AWeapon::GetAimDownSightsRotation()
{
	return AimDownSightsRotation;
}

FVector AWeapon::GetHipFireLocation()
{
	return HipFireLocation;
}

FRotator AWeapon::GetHipFireRotation()
{
	return HipFireRotation;
}