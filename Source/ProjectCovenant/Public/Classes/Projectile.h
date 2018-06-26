// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class AWeapon;

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

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetWeapon(AWeapon * NewWeapon);

	virtual void SetDamage(float NewDamage);

	virtual void SetSpeed(float NewSpeed);

	virtual float GetSpeed();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent * Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent * ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent * CollisionCapsule;

	UPROPERTY()
	AWeapon * Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxDamage = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float FallOff = 0.3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float IntialVelocity = 1000.f;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDestructionSound();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayWhizzingSound();

};
