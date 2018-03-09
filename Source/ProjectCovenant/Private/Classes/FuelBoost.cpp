// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "SubjectZero.h"
#include "FuelBoost.h"


// Sets default values
AFuelBoost::AFuelBoost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AFuelBoost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFuelBoost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AFuelBoost::AddFuel(ASubjectZero * player) {
	if(HasAuthority())
	{
		player->IncreaseFuel(FuelBoostPercentage);
	}
	return true;
}

