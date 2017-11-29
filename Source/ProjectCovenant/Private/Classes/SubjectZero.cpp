// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Classes/SubjectZero.h"
//#include "UnrealNetwork.h"


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
	GetCharacterMovement()->GravityScale = 1.f;
	GetCharacterMovement()->JumpZVelocity = JumpSpeed;
	GetCharacterMovement()->GetPhysicsVolume()->TerminalVelocity = 10000.f;
	
}

// Called every frame
void ASubjectZero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Time = DeltaTime;

	Grounded = !GetCharacterMovement()->IsFalling();
	JetpackActive = JetpackActive && Fuel > 0.f && !Grounded;
	Velocity = GetVelocity();

	// Movement depends on if grounded or in the air
	if (Grounded)
	{
		GetCharacterMovement()->MaxAcceleration = GroundAcceleration;

		if (Sprinting)
		{
			GetCharacterMovement()->MaxWalkSpeed = MaxGroundSpeed * 2.f;
		} 
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = MaxGroundSpeed;
		}

		// Jump
		if (Jumping)
		{
			Jump();
		}
		else
		{
			JetpackActive = false;
		}

		Move();
	}
	else
	{	
		ApplyAirResistance();
		if(JetpackActive)
		{
			JetpackBurst();
		}
		else
		{
			Move();
		}
	}
}

void ASubjectZero::Move()
{
	if(Controller)
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0;

		AddMovementInput(Rotation.RotateVector(Movement.GetSafeNormal()), 1.f);
	}
}

void ASubjectZero::JetpackBurst()
{
	if(Controller)
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0;

		FVector RotatedMovement = Rotation.RotateVector(Movement);

		// Create a vector that represents the movement of the character within the world
		FVector Force = JetpackAcceleration * FVector(RotatedMovement.X, RotatedMovement.Y, Jumping ? 1.f : 0.f);
		GetCharacterMovement()->AddForce(Force);
		DepleteJetpack();
	}
}

void ASubjectZero::DepleteJetpack()
{
	float FuelUsed = FuelUsage * ((Movement.X != 0.f ? 1.f : 0.f) + (Movement.Y != 0.f ? 1.f : 0.f) + (Movement.Z != 0.f ? 1.f : 0.f)) * (Sprinting ? 3.f : 1.f);
	Fuel = Fuel - (FuelUsed * Time);
}

void ASubjectZero::ApplyAirResistance()
{
	FVector Force;
	float Magnitude = Velocity.Size();
	FVector Direction = -1.f * Velocity.GetSafeNormal();
	Force = Direction * (Magnitude * Magnitude) * AirResistanceConstant;
	GetCharacterMovement()->AddForce(Force);
}

// Getters
float ASubjectZero::GetSpeed() const { return GetVelocity().Size()/100.f; }
float ASubjectZero::GetVerticalSpeed() const { return GetVelocity().Z; }
float ASubjectZero::GetMaxHealth() { return MaxHealth; }
float ASubjectZero::GetHealth() { return Health; }
float ASubjectZero::GetMaxArmor() const { return MaxArmor; }
float ASubjectZero::GetArmor() const { return Armor; }
float ASubjectZero::GetMaxShield() const { return MaxShield; }
float ASubjectZero::GetShield() const { return Shield; }
float ASubjectZero::GetMaxFuel() const { return MaxFuel; }
float ASubjectZero::GetFuel() const { return Fuel; }
bool ASubjectZero::IsJetpackActive() const { return JetpackActive; }

// Input methods
void ASubjectZero::SetupPlayerInputComponent(class UInputComponent* Input)
{
	// Movement binds
	Input->BindAxis("Yaw", this, &ASubjectZero::AddControllerYawInput);
	Input->BindAxis("Pitch", this, &ASubjectZero::AddControllerPitchInput);
	Input->BindAction("Jump", IE_Pressed, this, &ASubjectZero::InputJumpPress);
	Input->BindAction("Jump", IE_Released, this, &ASubjectZero::InputJumpRelease);
	Input->BindAction("Sprint", IE_Pressed, this, &ASubjectZero::InputSprintPress);
	Input->BindAction("Sprint", IE_Released, this, &ASubjectZero::InputSprintRelease);
	Input->BindAction("Forward", IE_Pressed, this, &ASubjectZero::InputForwardPress);
	Input->BindAction("Forward", IE_Released, this, &ASubjectZero::InputForwardRelease);
	Input->BindAction("Backward", IE_Pressed, this, &ASubjectZero::InputBackwardPress);
	Input->BindAction("Backward", IE_Released, this, &ASubjectZero::InputBackwardRelease);
	Input->BindAction("Left", IE_Pressed, this, &ASubjectZero::InputLeftPress);
	Input->BindAction("Left", IE_Released, this, &ASubjectZero::InputLeftRelease);
	Input->BindAction("Right", IE_Pressed, this, &ASubjectZero::InputRightPress);
	Input->BindAction("Right", IE_Released, this, &ASubjectZero::InputRightRelease);
}

void ASubjectZero::InputForwardPress() { Movement.X += 1.f; }
void ASubjectZero::InputForwardRelease() { Movement.X += -1.f; }
void ASubjectZero::InputBackwardPress() { Movement.X += -1.f; }
void ASubjectZero::InputBackwardRelease() { Movement.X += 1.f; }
void ASubjectZero::InputLeftPress() { Movement.Y += -1.f; }
void ASubjectZero::InputLeftRelease() { Movement.Y += 1.f; }
void ASubjectZero::InputRightPress() { Movement.Y += 1.f; }
void ASubjectZero::InputRightRelease() { Movement.Y += -1.f; }

void ASubjectZero::InputJumpPress()
{
	if(Controller)
	{
		Movement.Z = 1.f;
		Jumping = true;
		if(!Grounded)
		{
			JetpackActive = Fuel > 0.f;
		}
	}
}

void ASubjectZero::InputJumpRelease()
{
	Movement.Z = 0.f;
	Jumping = false;
}

void ASubjectZero::InputSprintPress()
{
	Sprinting = true;
}

void ASubjectZero::InputSprintRelease()
{
	Sprinting = false;
}

void ASubjectZero::Log(FString msg)
{
	if (GEngine && LogsOn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, msg);
	}
}