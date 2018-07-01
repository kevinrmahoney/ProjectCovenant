// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "SubjectZero.h"
#include "Weapon.h"
#include "Interactable.h"
#include "Interactor.h"


// Sets default values for this component's properties
UInteractor::UInteractor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInteractor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInteractor::Interact()
{
	if (ASubjectZero * Character = Cast<ASubjectZero>(GetOwner()))
	{
		Logger::Log("Character name is " + Character->GetName());
		FHitResult HitResult = GetFirstActor();
		if (AInteractable * Interactable = Cast<AInteractable>(HitResult.Actor.Get()))
		{
			Logger::Log("Interactable Name: " + Interactable->GetName());
			Interactable->Interact(Character);
		}
		else
		{
			AActor * ActorHit = HitResult.Actor.Get();
			if(ActorHit)
			{
				Logger::Log("Actor hit isnt interactable: " + ActorHit->GetName());
			}
			else
			{
				Logger::Log("Actor not hit");
			}
		}
	}
	else
	{
		Logger::Log("Couldn't cast character");
	}
}

const FHitResult UInteractor::GetFirstActor() 
{
	DrawDebugLine(GetWorld(), GetReachStart(), GetReachEnd(), FColor::Red, false, 2.f);
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		GetReachStart(),
		GetReachEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		TraceParameters
	);

	return Hit;
}

FVector UInteractor::GetReachStart() 
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	return PlayerViewPointLocation;
}

FVector UInteractor::GetReachEnd() 
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

