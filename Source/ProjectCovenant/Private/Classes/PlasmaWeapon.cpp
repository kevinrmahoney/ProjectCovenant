// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "PlasmaWeapon.h"


// Sets default values
APlasmaWeapon::APlasmaWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlasmaWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlasmaWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

