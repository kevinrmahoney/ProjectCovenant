// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableObject.generated.h"

class ASubjectZero;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTCOVENANT_API IInteractableObject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(ASubjectZero * Interactor);
	
};
