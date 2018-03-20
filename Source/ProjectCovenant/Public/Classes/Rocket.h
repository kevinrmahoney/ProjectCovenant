// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Projectile.h"
#include "Rocket.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ARocket : public AProjectile
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ARocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent * Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent * ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxDamage = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float FallOff = 0.3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float IntialVelocity = 1000.f;
	
};
