// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Item.h"
#include "UnrealNetwork.h"
#include "SubjectZero.h"
#include "Weapon.h"
#include "BaseMode.h"
#include "BaseState.h"


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

	// Disable gravity, physics and collision
	GunMesh->SetEnableGravity(false);
	GunMesh->SetSimulatePhysics(false);
	GunMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GunMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GunMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GunMesh->SetGenerateOverlapEvents(false);

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

	// Adding functions to execute through events must be done in BeginPlay()
	if(HasAuthority())
	{
		GunMesh->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBeginOverlap);
	}
}

void AWeapon::Destroyed()
{
	if(RecoilComponent)
	{
		RecoilComponent->Deactivate();
	}

	AimDownSights(false);

	if(Item)
	{
		Item->LastShotTimeStamp = GetWorld()->GetRealTimeSeconds() - FireRateProgress;
		Item->UnequipTimeStamp = GetWorld()->GetRealTimeSeconds();
	}
	Super::Destroyed();
}

UItem * AWeapon::GetItem()
{
	return Item;
}

void AWeapon::SetItem(UItem * NewItem)
{
	if(GetLocalRole() == ROLE_Authority || GetLocalRole() == ROLE_AutonomousProxy)
	{
		if(NewItem)
		{
			Item = NewItem;

			FireRateProgress = UGameplayStatics::GetRealTimeSeconds(GetWorld()) - Item->LastShotTimeStamp, FireRate;
		}
		else
		{
			Logger::Error("Attempting to set NULL item for " + GetName());
		}
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
	
}

bool AWeapon::CanFire()
{
	return WeaponSwitchCooldownProgress >= WeaponSwitchCooldown;
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
}

void AWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(HasAuthority())
	{
		if(ASubjectZero * Character = Cast<ASubjectZero>(OtherActor))
		{
			if(Character != Shooter)
			{
				ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode());
				if(Mode)
				{
					ABaseState * State = Cast<ABaseState>(Mode->GameState);
					if(State)
					{
						Logger::Log("Destroying weapon " + GetName() + " after collision with " + Character->GetName());
						Mode->GiveItemToCharacter(Character, State->GetItemFromActorClass(this));
						Destroy();
					}
				}
			}
		}
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
	FVector StartPoint = FVector(Muzzle->GetComponentLocation());
	FVector EndPoint;
	for(FVector V : ShotVectors)
	{
		EndPoint = StartPoint + FVector(Muzzle->GetComponentRotation().RotateVector(V));
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 2.f);
	}
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