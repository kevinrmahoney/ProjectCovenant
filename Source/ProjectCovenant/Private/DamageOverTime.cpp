// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "DamageOverTime.h"
#include "SubjectZero.h"



ADamageOverTime::ADamageOverTime() {
	
}

void ADamageOverTime::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	Logger::Log("ticking..");
}

void ADamageOverTime::IncrementCount() {
	Count++;
	PrimaryActorTick.bCanEverTick = true;
	Logger::Log(FString::FromInt(Count));
}

void ADamageOverTime::DecrementCount() {
	Count--;
	Logger::Log(FString::FromInt(Count));
}

void ADamageOverTime::BeginPlay() {
	PrimaryActorTick.bStartWithTickEnabled = false;
}