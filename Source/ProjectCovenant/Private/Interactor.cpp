// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "SubjectZero.h"
#include "Weapon.h"
#include "Interactable.h"
#include "Interactor.h"


// Sets default values for this component's properties
AInteractor::AInteractor()
{
	SetReplicates(true);
	SetReplicateMovement(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetSimulatePhysics(true);
}


// Called when the game starts
void AInteractor::BeginPlay()
{
	Super::BeginPlay();
}

AInteractable * AInteractor::Interact()
{
	// Do a raycast in front and return the actor that is hit, if its an Interactable actor
	if (ASubjectZero * Character = Cast<ASubjectZero>(this))
	{
		FHitResult HitResult = GetFirstActor();
		if (AInteractable * Interactable = Cast<AInteractable>(HitResult.Actor.Get()))
		{
			Logger::Log("Character " + Character->GetName() + " interacted with Interactable " + Interactable->GetName());
			return Interactable;
		}
	}
	return nullptr;
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

