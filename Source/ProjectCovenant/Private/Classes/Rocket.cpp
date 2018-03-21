// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Rocket.h"
#include "BaseMode.h"
#include "SubjectZero.h"

ARocket::ARocket()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionCapsule->OnComponentHit.AddDynamic(this, &ARocket::OnHit);
}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
	Super::BeginPlay();
	CollisionCapsule->OnComponentHit.AddDynamic(this, &ARocket::OnHit);
	PlayWhizzingSound();
}

// Called every frame
void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARocket::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	PlayDestructionSound();
	if(HasAuthority())
	{
		Logger::Chat("EXPLOSION!");
		if(OtherActor)
		{
			Logger::Chat(OtherActor->GetName());
		}
		// Play destroy sound
		// Do a sphere trace
		// For loop of all actors caught in trace
		// Apply an impulse to all actors
		// Destroy this actor

		TArray<FHitResult> OutHits;
		FVector Epicenter = GetActorLocation();
		FCollisionShape ExplosionSphere = FCollisionShape::MakeSphere(Radius);
		float ExplosionForce = 1000.f;

		bool IsHit = GetWorld()->SweepMultiByChannel(OutHits, Epicenter, Epicenter, FQuat::Identity, ECC_WorldStatic, ExplosionSphere);

		//TODO: Save the player that shot the rocket, and the weapon (or just the weapon, and use Shooter variable stored to obtain shooter)
		//TODO: apply percentage of damage to player, rather than full damage
		if(IsHit)
		{
			for(auto& Result : OutHits)
			{
				AActor * HitActor = Result.GetActor();
				if(HitActor && HitActor != this)
				{
					FVector ExplosionDirection = (HitActor->GetRootComponent()->GetComponentLocation() - Epicenter);
					float Scale = Radius = 1.f - (ExplosionDirection.Size()/Radius);
					ExplosionDirection = ExplosionDirection.GetSafeNormal();
					Logger::Chat(Scale);
					ExplosionDirection.Z = ExplosionDirection.Z * 1.5f;
					Logger::Chat("HitActor: " + HitActor->GetName());
					if(ASubjectZero * Player = Cast<ASubjectZero>(HitActor))
					{
						Logger::Chat(ExplosionDirection.ToString());
						Player->GetCharacterMovement()->AddImpulse(ExplosionForce * ExplosionDirection, true);
						//Player->GetMovementComponent()->Velocity+= ExplosionForce * ExplosionDirection;
						ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode());
						float TotalDamage = FMath::Max(MinDamage, MaxDamage * Scale);
						if(Mode)
						{
							Mode->DealDamage(nullptr, Player, TotalDamage, nullptr);
						}
					}
					UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(HitActor->GetRootComponent());
					if(MeshComp)
					{
						Logger::Chat(MeshComp->GetName());
						//MeshComp->AddRadialImpulse(Epicenter, 500.f, 200.f, ERadialImpulseFalloff::RIF_Linear, true);
					}
				}
			}
		}
	}
	Destroy();
}