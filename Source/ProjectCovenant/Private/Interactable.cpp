// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Interactable.h"
#include "UnrealNetwork.h"
#include "SubjectZero.h"


// Sets default values for this component's properties
AInteractable::AInteractable()
{
	SetReplicates(true);
	SetReplicateMovement(true);
	GetStaticMeshComponent()->SetIsReplicated(true);
	GetStaticMeshComponent()->SetEnableGravity(true);
	GetStaticMeshComponent()->SetSimulatePhysics(true);
	GetStaticMeshComponent()->SetCollisionProfileName(FName("Interactable"));
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
}

void AInteractable::SetMesh(UStaticMesh * NewMesh)
{
	GetStaticMeshComponent()->SetStaticMesh(NewMesh);
	GetStaticMeshComponent()->SetMassOverrideInKg(NAME_None, 10.f, true);
}