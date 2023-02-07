// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Gas.generated.h"

UCLASS()
class PROJECTCOVENANT_API AGas : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGas();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
