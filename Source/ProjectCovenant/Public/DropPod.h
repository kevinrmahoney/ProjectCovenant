// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interactable.h"
#include "InteractableObject.h"
#include "DropPod.generated.h"

UCLASS()
class PROJECTCOVENANT_API ADropPod : public APawn, public IInteractableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADropPod();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent * Base;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent * DropPodMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent * DropPodDoorMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UCameraComponent * Camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void Interact(ASubjectZero * Interactor) override;

};
