// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Plasma.h"
#include "BaseMode.h"
#include "SubjectZero.h"
#include "Weapon.h"

APlasma::APlasma()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlasma::BeginPlay()
{
	Super::BeginPlay();
	if(HasAuthority())
	{
		CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &APlasma::OnBeginOverlap);
		CollisionCapsule->OnComponentHit.AddDynamic(this, &APlasma::OnHit);
	}
}

// Called every frame
void APlasma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayWhizzingSound();
}

void APlasma::Explode(AActor * DirectHitActor, UPrimitiveComponent * HitComponent)
{
	if(HasAuthority())
	{
		if(ASubjectZero * Player = Cast<ASubjectZero>(DirectHitActor))
		{
			ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode());

			if(Mode)
			{
				if(Weapon)
				{
					Mode->DealDamage(Weapon->Shooter, Player, Damage, Weapon, HitComponent);
				}
				else
				{
					Mode->DealDamage(nullptr, Player, Damage, nullptr, HitComponent);
				}
			}
		}
		PlayDestructionSound();
		Destroy();
	}
}

void APlasma::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if(WeaponHasBeenSet)
	{
		if(Weapon && Weapon->Shooter == OtherActor)
		{
		}
		else
		{
			Explode(OtherActor, OtherComponent);
		}
	}
}

void APlasma::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(WeaponHasBeenSet)
	{
		if(Weapon && Weapon->Shooter == OtherActor)
		{
		}
		else
		{
			Explode(OtherActor, OtherComp);
		}
	}
}

void APlasma::SetWeapon(AWeapon * NewWeapon)
{
	Weapon = NewWeapon;
	WeaponHasBeenSet = true;
}

void APlasma::Destroyed()
{
	PlayDestructionSound();
}