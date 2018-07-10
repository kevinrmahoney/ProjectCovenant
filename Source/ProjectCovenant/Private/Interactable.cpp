// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Interactable.h"
#include "UnrealNetwork.h"
#include "SubjectZero.h"
#include "BaseMode.h"
#include "BaseState.h"


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

// Add default functionality here for any IInteractableObject functions that are not pure virtual.
void AInteractable::Interact(ASubjectZero * Interactor)
{
	if(HasAuthority())
	{
		ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode());
		if(Mode)
		{
			ABaseState * State = Cast<ABaseState>(Mode->GameState);
			if(State)
			{
				Mode->GiveItemToCharacter(Interactor, State->GetItemFromStaticMesh(GetStaticMeshComponent()->GetStaticMesh()));
				Destroy();
			}
		}
	}
}