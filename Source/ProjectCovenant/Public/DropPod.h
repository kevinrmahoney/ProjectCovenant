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

	UPROPERTY(Replicated)
	FVector Velocity = FVector::ZeroVector;

	float DropAcceleration = 10.f;
	float Acceleration = 20.f;
	float MaxSpeed = 10000.f;
	float TerminalVelocity = -10000.f;
	float AirResistanceConstant = 0.00004f;

	UPROPERTY(Replicated)
	bool HasLanded = false;

	UFUNCTION()
	void Move(float Time);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetMovement(FVector NewMovement);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetRotation(FRotator NewRotation);

	UPROPERTY(Replicated, ReplicatedUsing = UpdateLocation)
	FVector ReplicatedLocation;

	UPROPERTY(Replicated, ReplicatedUsing = UpdateRotation)
	FRotator ReplicatedRotation;

	UFUNCTION()
	void UpdateLocation();

	UFUNCTION()
	void UpdateRotation();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	// Functions to deal with a player entering a Drop Pod
	UFUNCTION()
	void Enter(ASubjectZero * NewOccupant);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerEnter(ASubjectZero * NewOccupant);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastEnter(ASubjectZero * NewOccupant);

	// Functions to deal with a player leaving a Drop Pod
	UFUNCTION()
	void Leave();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerLeave();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastLeave();

	void SetOccupant(ASubjectZero * NewOccupant);

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
