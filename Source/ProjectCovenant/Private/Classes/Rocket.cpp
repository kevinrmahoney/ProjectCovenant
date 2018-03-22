// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Rocket.h"
#include "BaseMode.h"
#include "SubjectZero.h"
#include "Weapon.h"

ARocket::ARocket()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
	Super::BeginPlay();
	if(HasAuthority())
	{
		//CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ARocket::OnBeginOverlap);
		CollisionCapsule->OnComponentHit.AddDynamic(this, &ARocket::OnHit);
	}
}

// Called every frame
void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayWhizzingSound();
}

void ARocket::Explode(AActor * DirectHitActor)
{
	PlayDestructionSound();
	if(HasAuthority())
	{
		TArray<FHitResult> OutHits;
		FVector Epicenter = GetActorLocation();
		FCollisionShape ExplosionSphere = FCollisionShape::MakeSphere(Radius);
		float ExplosionForce = 1000.f;
		bool IsHit = GetWorld()->SweepMultiByChannel(OutHits, Epicenter, Epicenter, FQuat::Identity, ECC_WorldStatic, ExplosionSphere);

		if(IsHit)
		{
			for(auto& Result : OutHits)
			{
				AActor * HitActor = Result.GetActor();
				if(HitActor)
				{
					FVector ExplosionDirection = (HitActor->GetRootComponent()->GetComponentLocation() - Epicenter);
					float Scale = 1.f - (ExplosionDirection.Size() / Radius);

					ExplosionDirection = ExplosionDirection.GetSafeNormal();
					ExplosionDirection.Z = ExplosionDirection.Z * 1.5f;

					if(ASubjectZero * Player = Cast<ASubjectZero>(HitActor))
					{
						ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode());
						float TotalDamage = FMath::Max(MinDamage, MaxDamage * Scale);
						if(Weapon)
						{
							TotalDamage = Player == Weapon->Shooter ? TotalDamage * 0.5 : TotalDamage;
						}

						Player->GetCharacterMovement()->AddImpulse(ExplosionForce * ExplosionDirection, true);

						if(Mode)
						{
							if(Weapon)
							{
								Mode->DealDamage(Weapon->Shooter, Player, TotalDamage, Weapon);
							}
							else
							{
								Mode->DealDamage(nullptr, Player, TotalDamage, nullptr);
							}
						}
					}
				}
			}
		}
		Destroy();
	}
}

void ARocket::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if(WeaponHasBeenSet)
	{
		if(Weapon && Weapon->Shooter == OtherActor)
		{
		}
		else
		{
			Explode(OtherActor);
		}
	}
}

void ARocket::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(WeaponHasBeenSet)
	{
		if(Weapon && Weapon->Shooter == OtherActor)
		{
		}
		else
		{
			Explode(OtherActor);
		}
	}
}

void ARocket::SetWeapon(AWeapon * NewWeapon)
{
	Weapon = NewWeapon;
	WeaponHasBeenSet = true;
}