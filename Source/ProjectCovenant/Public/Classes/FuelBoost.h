// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FuelBoost.generated.h"

class ASubjectZero;

UCLASS()
class PROJECTCOVENANT_API AFuelBoost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuelBoost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool AddFuel(ASubjectZero * player);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float FuelBoostPercentage = 0.25f;
};
