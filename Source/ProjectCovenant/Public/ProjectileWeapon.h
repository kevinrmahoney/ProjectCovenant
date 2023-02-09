// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "ProjectileWeapon.generated.h"

class ASubjectZero;
class AProjectile;

UCLASS()
class PROJECTCOVENANT_API AProjectileWeapon : public AWeapon
{
	GENERATED_BODY()

// Sets default values for this actor's properties
public:
	AProjectileWeapon();

public:
	//(X=-6.456540,Y=-7.700000,Z=-148.210724)
	FVector AimDownSightsLocation = FVector(-6.456540f, -7.700000f, -148.210724f);
	//(Pitch=2.500000,Yaw=-11.700012,Roll=0.000000)
	FRotator AimDownSightsRotation = FRotator(2.500000f, -11.700012f, 0.000000f);

	//(X=1.575968,Y=11.798502,Z=-153.145187)
	FVector HipFireLocation = FVector(1.575968f, 11.798502f, -153.145187f);
	//(Pitch=3.000000,Yaw=-12.000000,Roll=0.000000)
	FRotator HipFireRotation = FRotator(3.000000f, -12.000000f, 0.000000f);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Reload = 1;

	UPROPERTY(BlueprintReadOnly)
	float ReloadProgress = 0.f;

	UPROPERTY(BlueprintReadOnly)
	bool IsReloading = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AmmoMax = 1;

	UPROPERTY(BlueprintReadOnly)
	float Ammo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void DealDamage(ASubjectZero * Victim, float TotalDamage) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ConstructShotVectors() override;

	virtual void Update(float DeltaTime) override;

	virtual bool CanFire() override;

	virtual void Fire() override;

	virtual void BeginReload();

	virtual float GetAmmo();

	virtual void SetItem(UItem * NewItem);

	virtual FVector GetAimDownSightsLocation() override;

	virtual FRotator GetAimDownSightsRotation() override;

	virtual FVector GetHipFireLocation() override;

	virtual FRotator GetHipFireRotation() override;

	void Destroyed() override;
};
