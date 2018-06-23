// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Item.h"
#include "UnrealNetwork.h"
#include "SubjectZero.h"
#include "Weapon.h"
#include "BaseMode.h"


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

	// Disable gravity, physics and collision by default
	GunMesh->SetEnableGravity(false);
	GunMesh->SetSimulatePhysics(false);
	GunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GunMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GunMesh->bGenerateOverlapEvents = false;

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"), false);
	Muzzle->AttachToComponent(GunMesh, FAttachmentTransformRules::KeepRelativeTransform);

	RecoilComponent = CreateDefaultSubobject<URecoil>(TEXT("RecoilComponent"), false);
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

	FireRateProgress = FireRate;
	ReloadProgress = Reload;

	// Adding functions to execute through events must be done in BeginPlay()
	if(HasAuthority())
	{
		GunMesh->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBeginOverlap);
	}
}

void AWeapon::ConstructShotVectors()
{
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Trigger)
	{
		if(CanFire())
		{
			Fire();
		}
	}

	// Update variables
	Update(DeltaTime);
}

void AWeapon::Update(float DeltaTime)
{
	FireRateProgress = FMath::Clamp(FireRateProgress + DeltaTime, 0.f, FireRate);

	if(IsReloading)
	{
		ReloadProgress = FMath::Clamp(ReloadProgress + DeltaTime, 0.f, Reload);
		if(ReloadProgress >= Reload)
		{
			Ammo = AmmoMax;
			IsReloading = false;
		}
	}
}

bool AWeapon::CanFire()
{
	return false;
}

void AWeapon::Fire()
{
	// Apply recoil
	if(RecoilComponent)
	{
		RecoilComponent->Recoil();
	}

	// Reset the the progress of the fire rate counter
	FireRateProgress = 0.f;

	// Draw visuals and play sounds
	DrawVisuals();
	PlayShootSound();
}

void AWeapon::BeginReload()
{
	if(Ammo < AmmoMax)
	{
		IsReloading = true;
		ReloadProgress = 0.f;
	}
	else
	{
		Logger::Chat("Cant reload");
	}
}

void AWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(HasAuthority())
	{
		if(ASubjectZero * Character = Cast<ASubjectZero>(OtherActor))
		{
			if(Character != Shooter)
			{
				if(ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode()))
				{
					Mode->GiveItemToCharacter(Character, Mode->GetItem(this));
					Destroy();
				}
			}
		}
	}
}

void AWeapon::Drop()
{
	GunMesh->SetEnableGravity(true);
	GunMesh->SetSimulatePhysics(true);
	GunMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GunMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GunMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	GunMesh->bGenerateOverlapEvents = true;
}

void AWeapon::SetItem(UItem * NewItem)
{
	if(Role == ROLE_Authority || Role == ROLE_AutonomousProxy)
	{
		Item = NewItem;
		FireRateProgress = FMath::Min(UGameplayStatics::GetRealTimeSeconds(GetWorld()) - Item->LastShotTimeStamp, FireRate);
		FireRateProgress = FireRateProgress - WeaponSwitchCooldown;
	}
}

void AWeapon::SetShooter(ASubjectZero * NewShooter)
{
	Shooter = NewShooter;
	if(RecoilComponent)
	{
		RecoilComponent->SetShooter(Shooter);
	}
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
	ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode());
	if(Mode)
	{
		Mode->DealDamage(Shooter, Victim, TotalDamage, this);
	}
}

void AWeapon::DrawDebugVisuals()
{
}

void AWeapon::AimDownSights(bool IsAimDownSights)
{
	if (Shooter && Shooter->FirstPersonMesh)
	{
		if (IsAimDownSights)
		{
			Shooter->FirstPersonMesh->SetRelativeLocation(GetAimDownSightsLocation());
			Shooter->FirstPersonMesh->SetRelativeRotation(GetAimDownSightsRotation());
		}
		else
		{
			Shooter->FirstPersonMesh->SetRelativeLocation(GetHipFireLocation());
			Shooter->FirstPersonMesh->SetRelativeRotation(GetHipFireRotation());
		}
	}
}

float AWeapon::GetAmmo()
{
	return Ammo;
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

void AWeapon::Destroyed()
{
	if(RecoilComponent)
	{
		RecoilComponent->Deactivate();
	}
	AimDownSights(false);

	//delete RecoilComponent;
	Super::Destroyed();
}