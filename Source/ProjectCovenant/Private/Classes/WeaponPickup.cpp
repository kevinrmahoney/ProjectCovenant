// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "WeaponPickup.h"
#include "SubjectZero.h"
#include "Item.h"
#include "BaseMode.h"


// Sets default values
AWeaponPickup::AWeaponPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(BoxComponent);

	PickupWeapon = CreateDefaultSubobject <UChildActorComponent>(TEXT("PickupWeapon"));
	PickupWeapon->AttachToComponent(BoxComponent, FAttachmentTransformRules::KeepRelativeTransform);

	TimeSinceRespawn = RespawnTime;
}

// Called when the game starts or when spawned
void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeSinceRespawn += DeltaTime;

	if(TimeSinceRespawn >= RespawnTime)
	{
		PickupWeapon->SetVisibility(true);
		TArray<AActor*> OverlappingActors;
		BoxComponent->GetOverlappingActors(OverlappingActors);

		if( OverlappingActors.Num() > 0)
		{
			if(ASubjectZero * Player = Cast<ASubjectZero>(OverlappingActors[0]))
			{
				GivePlayerWeapon(Player);
			}
			TimeSinceRespawn = 0.f;
			PickupWeapon->SetVisibility(false);
		}
	}

}

void AWeaponPickup::GivePlayerWeapon(ASubjectZero * player)
{
	if(HasAuthority())
	{
		UItem * WeaponItem = NewObject<UItem>(this, "NewWeapon");
		WeaponItem->ItemID = GetItemID(PickupWeapon->GetChildActorClass());

		if(ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode()))
		{
			Mode->GiveItemToCharacter(player, WeaponItem);
		}
	}
}