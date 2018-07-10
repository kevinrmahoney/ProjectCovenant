// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableObject.h"
#include "Interactable.generated.h"

class ASubjectZero;

UCLASS()
class PROJECTCOVENANT_API AInteractable : public AStaticMeshActor, public IInteractableObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AInteractable();

	void SetMesh(UStaticMesh * NewMesh);

	virtual void Interact(ASubjectZero * Interactor) override;
};
