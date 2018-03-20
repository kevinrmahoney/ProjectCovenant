// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class PROJECTCOVENANT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	USceneComponent * Root;

	UStaticMeshComponent * Mesh;

	UProjectileMovementComponent * ProjectileMovementComponent;

	float MaxDamage = 100.f;

	float FallOff = 0.3;

	float IntialVelocity = 1000.f;

};
