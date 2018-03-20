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

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"), false);
	CollisionCapsule->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketMesh"), false);
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Mesh->SetVisibility(true);
	Mesh->SetOnlyOwnerSee(false);
	Mesh->SetOwnerNoSee(false);
	Mesh->SetEnableGravity(false);

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