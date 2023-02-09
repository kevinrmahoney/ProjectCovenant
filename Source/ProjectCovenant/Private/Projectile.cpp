// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
	SetReplicateMovement(true);

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"), false);
	SetRootComponent(CollisionCapsule);
	CollisionCapsule->SetCollisionProfileName(TEXT("Projectile"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketMesh"), false);
	Mesh->AttachToComponent(CollisionCapsule, FAttachmentTransformRules::KeepRelativeTransform);
	Mesh->SetVisibility(true);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"), false);
	ProjectileMovementComponent->InitialSpeed = IntialVelocity;
	ProjectileMovementComponent->MaxSpeed = IntialVelocity;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::SetWeapon(AWeapon * NewWeapon)
{
	Weapon = NewWeapon;
}

void AProjectile::SetDamage(float NewDamage) 
{
	Damage = NewDamage;
}

void AProjectile::SetSpeed(float NewSpeed)
{
	ProjectileMovementComponent->InitialSpeed = NewSpeed;
	ProjectileMovementComponent->MaxSpeed = NewSpeed;
	ProjectileMovementComponent->Velocity = ProjectileMovementComponent->Velocity.GetSafeNormal() * NewSpeed;
	ProjectileMovementComponent->UpdateComponentVelocity();
}

float AProjectile::GetSpeed()
{
	return ProjectileMovementComponent->Velocity.Size();
}