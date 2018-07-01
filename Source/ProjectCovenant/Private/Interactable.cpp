// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Interactable.h"
#include "UnrealNetwork.h"
#include "SubjectZero.h"


// Sets default values for this component's properties
AInteractable::AInteractable()
{

}

void AInteractable::Interact(ASubjectZero * CharacterWhoInteracted)
{
	Logger::Log("Interactable.Interact: " + CharacterWhoInteracted->GetName());
	//Logger::Chat("Interactable.Interact: " + GetOwner()->GetName());
	if(Role != ROLE_Authority)
	{
		ServerInteract(CharacterWhoInteracted);
	}
}

void AInteractable::ServerInteract_Implementation(ASubjectZero * CharacterWhoInteracted)
{
	Interact(CharacterWhoInteracted);
}

bool AInteractable::ServerInteract_Validate(ASubjectZero * CharacterWhoInteracted)
{
	return true;
}