// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interactable.h"
#include "InteractableObject.h"
#include "DropPod.generated.h"

class ASubjectZero;

UCLASS()
class PROJECTCOVENANT_API ADropPod : public APawn, public IInteractableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADropPod();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UBoxComponent * CollisionBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UBoxComponent * InteractionBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent * DropPodMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent * DropPodDoorMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UCameraComponent * Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent * OccupantSocket;

	UPROPERTY()
	ASubjectZero * Occupant;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void Interact(ASubjectZero * Interactor) override;

private:
	FVector Movement = FVector::ZeroVector;
	FVector Velocity = FVector::ZeroVector;

	float Acceleration = 20.f;
	float MaxSpeed = 100.f;
	float TerminalVelocity = -10000.f;

	bool HasLanded = false;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void Enter();
	void Leave();
	void InputYaw(float Value);
	void InputPitch(float Value);
	void InputForwardPress();
	void InputForwardRelease();
	void InputBackwardPress();
	void InputBackwardRelease();
	void InputLeftPress();
	void InputLeftRelease();
	void InputRightPress();
	void InputRightRelease();
	void InputJumpPress();
	void InputJumpRelease();
	void InputCrouchPress();
	void InputCrouchRelease();
	void InputInteractPress();
};
