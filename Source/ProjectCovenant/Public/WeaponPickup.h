// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponPickup.generated.h"

class ASubjectZero;

UCLASS()
class PROJECTCOVENANT_API AWeaponPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float TimeSinceRespawn;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GivePlayerWeapon(ASubjectZero * player);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent * BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UChildActorComponent * PickupWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float RespawnTime = 30.f;
};
