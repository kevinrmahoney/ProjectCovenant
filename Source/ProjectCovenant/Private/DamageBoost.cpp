// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "SubjectZero.h"
#include "DamageBoost.h"


// Sets default values
ADamageBoost::ADamageBoost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADamageBoost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageBoost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ADamageBoost::DamageBoostBegin(ASubjectZero * player) {
	if(HasAuthority())
	{
		player->DamageBoost(BoostMultiplier, BoostDuration);
	}
	return true;
}