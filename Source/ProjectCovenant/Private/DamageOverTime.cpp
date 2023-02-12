// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "DamageOverTime.h"
#include "SubjectZero.h"
#include "BaseMode.h"

ADamageOverTime::ADamageOverTime() {
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);
}

void ADamageOverTime::BeginPlay() {
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ADamageOverTime::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ADamageOverTime::OnOverlapEnd);

	if(HasAuthority())
		BaseMode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode());
}

void ADamageOverTime::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		for (ASubjectZero* Player : PlayersOverlapping)
		{
			FDamageEvent Damage;
			BaseMode->DealDamage(nullptr, Player, DamageAmount * DeltaTime, nullptr, nullptr);			
		}
	}
}

void ADamageOverTime::IncrementCount() {
	Count++;
}

void ADamageOverTime::DecrementCount() {
	Count--;
}


void ADamageOverTime::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	ASubjectZero* PlayerChar = Cast<ASubjectZero>(OtherActor);
	if(PlayerChar)
	{
		PlayersOverlapping.Add(PlayerChar);
		IncrementCount();
	}
}

void ADamageOverTime::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	ASubjectZero* PlayerChar = Cast<ASubjectZero>(OtherActor);
	if (PlayerChar)
	{
		PlayersOverlapping.Remove(PlayerChar);
		DecrementCount();
	}
}