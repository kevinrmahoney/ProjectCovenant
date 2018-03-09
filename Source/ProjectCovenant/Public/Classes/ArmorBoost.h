// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArmorBoost.generated.h"

class ASubjectZero;

UCLASS()
class PROJECTCOVENANT_API AArmorBoost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArmorBoost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool AddArmor(ASubjectZero * player);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float ArmorBoostPercentage = 0.25f;
};
