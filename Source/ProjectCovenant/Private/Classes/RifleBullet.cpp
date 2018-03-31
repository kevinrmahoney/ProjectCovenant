// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "RifleBullet.h"
#include "BaseMode.h"
#include "SubjectZero.h"
#include "Weapon.h"

ARifleBullet::ARifleBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARifleBullet::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ARifleBullet::OnBeginOverlap);
		CollisionCapsule->OnComponentHit.AddDynamic(this, &ARifleBullet::OnHit);
	}
}

// Called every frame
void ARifleBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayWhizzingSound();
}

void ARifleBullet::Explode(AActor * DirectHitActor)
{
	if (HasAuthority())
	{
		if (ASubjectZero * Player = Cast<ASubjectZero>(DirectHitActor))
		{
			Logger::Chat(Player->GetName());
			ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode());

			if (Mode)
			{
				if (Weapon)
				{
					Mode->DealDamage(Weapon->Shooter, Player, Damage, Weapon);
				}
				else
				{
					Mode->DealDamage(nullptr, Player, Damage, nullptr);
				}
			}
		}
		PlayDestructionSound();
		Destroy();
	}
}

void ARifleBullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (WeaponHasBeenSet)
	{
		if (Weapon && Weapon->Shooter == OtherActor)
		{
		}
		else
		{
			if (OtherActor) { Logger::Log("Bullet hit " + OtherActor->GetName()); }
			Explode(OtherActor);
		}
	}
}

void ARifleBullet::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (WeaponHasBeenSet)
	{
		if (Weapon && Weapon->Shooter == OtherActor)
		{
		}
		else
		{
			Explode(OtherActor);
		}
	}
}

void ARifleBullet::SetWeapon(AWeapon * NewWeapon)
{
	Weapon = NewWeapon;
	WeaponHasBeenSet = true;
}

void ARifleBullet::Destroyed()
{
	PlayDestructionSound();
}


