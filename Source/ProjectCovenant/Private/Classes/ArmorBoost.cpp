// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "SubjectZero.h"
#include "ArmorBoost.h"


// Sets default values
AArmorBoost::AArmorBoost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AArmorBoost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArmorBoost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AArmorBoost::AddArmor(ASubjectZero * player) {
	if(HasAuthority())
	{
		player->IncreaseArmor(ArmorBoostPercentage);
	}
	return true;
}