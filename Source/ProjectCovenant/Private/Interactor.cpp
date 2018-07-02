// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "SubjectZero.h"
#include "Weapon.h"
#include "Interactable.h"
#include "Interactor.h"


// Sets default values for this component's properties
AInteractor::AInteractor()
{
}


// Called when the game starts
void AInteractor::BeginPlay()
{
	Super::BeginPlay();
}

AInteractable * AInteractor::Interact()
{
	AInteractable * Interactable = nullptr;
	if (ASubjectZero * Character = Cast<ASubjectZero>(this))
	{
		Logger::Log("Character name is " + Character->GetName());
		FHitResult HitResult = GetFirstActor();
		if (AInteractable * Interactable = Cast<AInteractable>(HitResult.Actor.Get()))
		{
			Logger::Log("Interactable Name: " + Interactable->GetName());
			return Interactable;
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
	return Interactable;
}

const FHitResult AInteractor::GetFirstActor() 
{
	DrawDebugLine(GetWorld(), GetReachStart(), GetReachEnd(), FColor::Red, false, 2.f);
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		GetReachStart(),
		GetReachEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return Hit;
}

FVector AInteractor::GetReachStart() 
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	return PlayerViewPointLocation;
}

FVector AInteractor::GetReachEnd() 
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

