// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "DropPod.h"


// Sets default values
ADropPod::ADropPod()
{
	Base = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	SetRootComponent(Base);

	// Mesh
	DropPodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropPod"));
	DropPodMesh->AttachToComponent(Base, FAttachmentTransformRules::KeepRelativeTransform);

	// Mesh
	DropPodDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropPodDoor"));
	DropPodDoorMesh->AttachToComponent(DropPodMesh, FAttachmentTransformRules::KeepRelativeTransform);

	// Create a CameraComponent 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	Camera->AttachToComponent(DropPodMesh, FAttachmentTransformRules::KeepRelativeTransform);

	// Position the camera a bit above the eyes
	Camera->RelativeLocation = FVector(0.f, 0, 250.f);
	// Allow the pawn to control rotation
	Camera->bUsePawnControlRotation = true;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADropPod::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADropPod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADropPod::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADropPod::Interact(ASubjectZero * Interactor)
{
}