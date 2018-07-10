// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableObject.h"
#include "Interactor.generated.h"

class AInteractable;

UCLASS()
class PROJECTCOVENANT_API UInteractor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Reach = 1000.f;

public:
	AInteractable * GetInteractable();

	IInteractableObject * GetInteractableObject();

private:
	const FHitResult GetFirstActor();
	FVector GetReachStart();
	FVector GetReachEnd();
};
