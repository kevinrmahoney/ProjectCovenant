// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "SubjectZero.h"


// Sets default values
ASubjectZero::ASubjectZero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASubjectZero::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Character: Subject Zero"));
	}
}

// Called every frame
void ASubjectZero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASubjectZero::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAxis("Vertical", this, &ASubjectZero::MoveForwardBackward);
	InputComponent->BindAxis("Horizontal", this, &ASubjectZero::MoveLeftRight);
}

void ASubjectZero::MoveForwardBackward(float Val)
{
	if (Controller && Val != 0.f)
	{
		FRotator Rotation = Controller->GetControlRotation();
	}
}

void ASubjectZero::MoveLeftRight(float Val)
{

}