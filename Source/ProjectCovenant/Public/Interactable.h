// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

class ASubjectZero;

UCLASS()
class PROJECTCOVENANT_API AInteractable : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AInteractable();
		
public:
	UFUNCTION()
	void Interact(ASubjectZero * CharacterWhoInteracted);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerInteract(ASubjectZero * CharacterWhoInteracted);
};
