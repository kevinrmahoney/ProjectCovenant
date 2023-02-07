// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Rocket.generated.h"

class AWeapon;

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

	float MaxDamage = 125.f;
	float MinDamage = 30.f;
	float Radius = 500.f;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void Destroyed() override;

private:
	void Explode(AActor * DirectHitActor);

	bool WeaponHasBeenSet = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetWeapon(AWeapon * NewWeapon) override;
	
};
