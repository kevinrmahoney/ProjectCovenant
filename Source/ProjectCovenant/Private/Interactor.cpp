// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "SubjectZero.h"
#include "Weapon.h"
#include "Interactable.h"
#include "Interactor.h"


// Sets default values for this component's properties
UInteractor::UInteractor()
{
}


// Called when the game starts
void UInteractor::BeginPlay()
{
	Super::BeginPlay();
}

AInteractable * UInteractor::GetInteractable()
{
	// Do a raycast in front and return the actor that is hit, if its an Interactable actor
	FHitResult HitResult = GetFirstActor();
	if (AInteractable * Interactable = Cast<AInteractable>(HitResult.Actor.Get()))
	{
		Logger::Log("Character " + GetOwner()->GetName() + " interacted with Interactable " + Interactable->GetName());
		return Interactable;
	}
	return nullptr;
}

const FHitResult UInteractor::GetFirstActor()
{
	//DrawDebugLine(GetWorld(), GetReachStart(), GetReachEnd(), FColor::Red, false, 2.f);
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		GetReachStart(),
		GetReachEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel4),
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

