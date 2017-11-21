// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "SubjectZero.h"


// Sets default values
ASubjectZero::ASubjectZero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = MaxGroundSpeed;
	GetCharacterMovement()->AirControl = NormalAirControl;
	GetCharacterMovement()->MaxAcceleration = GroundAcceleration;

}

// Called when the game starts or when spawned
void ASubjectZero::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		Log("Character: Subject Zero");
	}
}

// Called every frame
void ASubjectZero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Time = DeltaTime;

	Grounded = !GetCharacterMovement()->IsFalling();

	// If the character has landed, automatically turn off the jetpack
	if (Grounded)
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxGroundSpeed;
		GetCharacterMovement()->MaxAcceleration = GroundAcceleration;

	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxJetpackSpeed;
	}
	FVector Velocity = GetVelocity();
	Velocity.Z = 0.f;
	Log(FString::SanitizeFloat(Velocity.Size()));
}

void ASubjectZero::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	// Movement
	InputComponent->BindAxis("MoveForwardBackward", this, &ASubjectZero::MoveForwardBackward);
	InputComponent->BindAxis("MoveLeftRight", this, &ASubjectZero::MoveLeftRight);
	InputComponent->BindAxis("MouseLookHorizontal", this, &ASubjectZero::AddControllerYawInput);
	InputComponent->BindAxis("MouseLookVertical", this, &ASubjectZero::AddControllerPitchInput);
	InputComponent->BindAxis("Jump", this, &ASubjectZero::OnJump);
	InputComponent->BindAxis("Jetpack", this, &ASubjectZero::OnJetpack);
}

/* Move the character backwards or forwards depending on what input is pressed
	Val - value to move the character. 1 for forwards, -1 for backwards, 0 for no backwards or forwards movement
*/
void ASubjectZero::MoveForwardBackward(float Value)
{
	// If the controller exists and the value to move forward or backward is not 0
	if (Controller && Value != 0.f)
	{
		// Get rotation of the player
		FRotator Rotation = Controller->GetControlRotation();

		// If the character is moving on the ground or is falling, limit the pitch of the character to 0
		if( GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.f;
		}

		// Create a vector that represents the movement of the character within the world
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X) * Value;
		if (JetpackActive)
		{
			AddMovementInput(Direction, JetpackSpeed);
		}
		else
		{
			AddMovementInput(Direction, GroundSpeed);
		}
	}
}

void ASubjectZero::MoveLeftRight(float Value)
{

	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y) * Value;

		// add movement in that direction depending on the mode of travel
		if (JetpackActive)
		{
			AddMovementInput(Direction, JetpackSpeed);
		}
		else
		{
			AddMovementInput(Direction, GroundSpeed);
		}
	}
}

void ASubjectZero::JetpackBurst()
{
	FRotator Rotation = Controller->GetControlRotation();
	// Create a vector that represents the movement of the character within the world
	const FVector * Direction = new FVector(0.f, 0.f, 1.f);
	LaunchCharacter(*Direction * JetpackClimbSpeed, false, false);
}

void ASubjectZero::OnJump(float Value)
{
	if (Controller && Value != 0.f)
	{
		if (Grounded)
		{
			Jump();
		}
		else if (!Grounded && JetpackActive)
		{
			JetpackBurst();
		}
	}
}

void ASubjectZero::OnJetpack(float Value)
{
	if (!Grounded && Value != 0.f)
	{
		JetpackActive = true;
		GetCharacterMovement()->AirControl = JetpackAirControl;
		GetCharacterMovement()->MaxAcceleration = JetpackAcceleration;
	}
	else
	{
		JetpackActive = false;
		GetCharacterMovement()->AirControl = NormalAirControl;
		GetCharacterMovement()->MaxAcceleration = GroundAcceleration;
	}
}

void ASubjectZero::Log(FString msg) 
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, msg);
	}
}
