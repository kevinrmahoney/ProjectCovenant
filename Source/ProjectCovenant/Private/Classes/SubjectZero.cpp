// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Classes/SubjectZero.h"


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
	Log("Character: Subject Zero");

	// Set initial character movement characteristics
	GetCharacterMovement()->MaxWalkSpeed = MaxGroundSpeed;
	GetCharacterMovement()->AirControl = NormalAirControl;
	GetCharacterMovement()->MaxAcceleration = GroundAcceleration;
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->JumpZVelocity = JumpSpeed;
}

// Called every frame
void ASubjectZero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Time = DeltaTime;


	// TODO: Refactor code such that lateral movement is all done in one method using MoveDirection vector
	MoveDirection.Normalize();
	//Log("MoveDirection" + MoveDirection.ToString());

	Grounded = !GetCharacterMovement()->IsFalling();

	if (JetpackActive)
	{
		JetpackActive = Fuel > 0.f;
	}

	// If the character has landed, automatically turn off the jetpack
	if (Grounded)
	{
		JetpackActive = false;
		GetCharacterMovement()->MaxWalkSpeed = MaxGroundSpeed;
		GetCharacterMovement()->MaxAcceleration = GroundAcceleration;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxJetpackSpeed;
		GetCharacterMovement()->MaxAcceleration = JetpackAcceleration;
	}

	if (JetpackActive)
	{
		GetCharacterMovement()->AirControl = JetpackAirControl;
	}
	else
	{
		GetCharacterMovement()->AirControl = NormalAirControl;
	}
	MoveDirection = FVector(0.f, 0.f, 0.f);
}

void ASubjectZero::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	// Movement binds
	InputComponent->BindAxis("MoveForwardBackward", this, &ASubjectZero::MoveForwardBackward);
	InputComponent->BindAxis("MoveLeftRight", this, &ASubjectZero::MoveLeftRight);
	InputComponent->BindAxis("MouseLookHorizontal", this, &ASubjectZero::AddControllerYawInput);
	InputComponent->BindAxis("MouseLookVertical", this, &ASubjectZero::AddControllerPitchInput);
	InputComponent->BindAxis("Jump", this, &ASubjectZero::OnJump);
}

/* Move the character backwards or forwards depending on what input is pressed
	Value - value to move the character. 1 for forwards, -1 for backwards, 0 for no backwards or forwards movement
*/
void ASubjectZero::MoveForwardBackward(float Value)
{

	// If the controller exists and the value to move forward or backward is not 0
	if (Controller && Value != 0.f)
	{
		// Get rotation of the player
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0;

		// Create a unit vector that represents the direction of the character's current lateral movement
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X) * Value;
		FVector Velocity = GetVelocity();
		Velocity.Z = 0;
		Velocity.Normalize();
		MoveDirection = MoveDirection + Direction;
		//Log("MoveForwardBackward: " + Direction.ToString());

		// Determine if the character is attempting to decelerating by comparing the current direction of 
		// movement with the direction the player is attempting to move the character.
		bool Decelerating = (Direction + Velocity).Size() < 1.f;

		// Move character depending on if the jetpack is active and if grounded
		if (JetpackActive && !Grounded)
		{
			// If decelerating, multiply the magnitude of the acceleration by the multiplier
			if (Decelerating)
			{
				GetCharacterMovement()->MaxAcceleration = JetpackAcceleration * DecelerationMultiplier;
			}

			// Move character
			AddMovementInput(Direction, JetpackSpeedScale);
			DepleteJetpack();
		}
		else if(Grounded)
		{
			AddMovementInput(Direction, GroundSpeedScale);
		}
	}
}

void ASubjectZero::MoveLeftRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		// Get rotation of the player
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0;

		// Get direction of movement in Y axis
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y) * Value;
		FVector Velocity = GetVelocity();
		Velocity.Z = 0;
		Velocity.Normalize();

		MoveDirection = MoveDirection + Direction;
		//Log("MoveLeftRight: " + Direction.ToString());

		bool Decelerating = (Direction + Velocity).Size() < 1.f;

		// Move character depending on state of character and direction of character
		if (JetpackActive && !Grounded)
		{
			if (Decelerating)
			{
				GetCharacterMovement()->MaxAcceleration = JetpackAcceleration * DecelerationMultiplier;
			}
			AddMovementInput(Direction, JetpackSpeedScale);
			DepleteJetpack();
		}
		else if(Grounded)
		{
			AddMovementInput(Direction, GroundSpeedScale);
		}
	}
}

void ASubjectZero::JetpackBurst()
{
	// Create a vector that represents the movement of the character within the world
	const FVector * Direction = new FVector(0.f, 0.f, 1.f);
	LaunchCharacter(*Direction * JetpackClimbSpeed, false, false);
	DepleteJetpack();
}

void ASubjectZero::OnJump(float Value)
{
	if (Controller && Value != 0.f)
	{
		if (Grounded)
		{
			Jump();
		}
		else if (!Grounded)
		{
			JetpackActive = Fuel > 0.f;
			if (JetpackActive)
			{
				JetpackBurst();
			}
		}
	}
}

void ASubjectZero::DepleteJetpack() 
{
	Fuel = Fuel - FuelUsage * Time;
}

void ASubjectZero::Log(FString msg) 
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, msg);
	}
}

float ASubjectZero::GetSpeed() const
{
	return FVector2D(GetVelocity().X, GetVelocity().Y).Size();
}

float ASubjectZero::GetVerticalSpeed() const
{
	return GetVelocity().Z;
}

float ASubjectZero::GetMaxHealth() const
{
	return MaxHealth;
}

float ASubjectZero::GetHealth() const
{
	return Health;
}

float ASubjectZero::GetMaxArmor() const
{
	return MaxArmor;
}

float ASubjectZero::GetArmor() const
{
	return Armor;
}

float ASubjectZero::GetMaxShield() const
{
	return MaxShield;
}

float ASubjectZero::GetShield() const
{
	return Shield;
}

float ASubjectZero::GetMaxFuel() const
{
	return MaxFuel;
}

float ASubjectZero::GetFuel() const
{
	return Fuel;
}

bool ASubjectZero::IsJetpackActive() const
{
	return JetpackActive;
}