// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/HitscanWeapon.h"
#include "Railgun.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ARailgun : public AHitscanWeapon
{
	GENERATED_BODY()
	
public:
	ARailgun();
	
protected:
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//float Damage = 5.f;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//float Range = 20000.f;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//float Cooldown = 0.1f;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//float Falloff = 1.f;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//float Ammo = 100.f;

private:

	bool Trigger = false;
	float TimeSinceLastShot = 0.f;

public:
	//UPROPERTY()
	//ASubjectZero * Shooter = nullptr;

protected:
	//UPROPERTY()
	//USceneComponent * Root;

	//UPROPERTY(VisibleAnywhere)
	//UStaticMeshComponent * Mesh;

	//UPROPERTY(VisibleAnywhere)
	//USceneComponent * Muzzle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTrigger(bool T);

	void SetShooter(ASubjectZero * NewShooter);

private:
	void Shoot();

	void DealDamage(ASubjectZero * Victim);

	void DrawLaser(FVector * Begin, FVector * End, float Duration);
};
