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
	Log(GetVelocity().ToString());
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
	}
	else
	{	
		ApplyAirResistance();
		if (JetpackActive)
		{
			GetCharacterMovement()->MaxAcceleration = JetpackAcceleration;
			GetCharacterMovement()->MaxWalkSpeed = MaxJetpackSpeed;
			JetpackActiveTime += Time;
			JetpackBurst();
		}
	}

	Movement.Normalize();

	FRotator Rotation = Controller->GetControlRotation();
	Rotation.Pitch = 0;

	Movement = Rotation.RotateVector(Movement);
	AddMovementInput(Movement, 1.f);
}

void ASubjectZero::SetupPlayerInputComponent(class UInputComponent* Input)
{
	// Movement binds
	Input->BindAxis("MoveForwardBackward", this, &ASubjectZero::MoveForwardBackward);
	Input->BindAxis("MoveLeftRight", this, &ASubjectZero::MoveLeftRight);
	Input->BindAxis("MouseLookHorizontal", this, &ASubjectZero::AddControllerYawInput);
	Input->BindAxis("MouseLookVertical", this, &ASubjectZero::AddControllerPitchInput);
	Input->BindAction("Jump", IE_Pressed, this, &ASubjectZero::OnJumpPress);
	Input->BindAction("Jump", IE_Released, this, &ASubjectZero::OnJumpRelease);
	Input->BindAction("Sprint", IE_Pressed, this, &ASubjectZero::OnSprintPress);
	Input->BindAction("Sprint", IE_Released, this, &ASubjectZero::OnSprintRelease);
}

/* Move the character backwards or forwards depending on what input is pressed
	Value - value to move the character. 1 for forwards, -1 for backwards, 0 for no backwards or forwards movement
*/
void ASubjectZero::MoveForwardBackward(float Value)
{
	if (Controller)
	{
		Movement.X = Value;
	}
}

void ASubjectZero::MoveLeftRight(float Value)
{
	if (Controller)
	{
		Movement.Y = Value;
	}
}

void ASubjectZero::OnJumpPress()
{
	if (Controller)
	{
		Jumping = true;
		if (!Grounded)
		{
			JetpackActive = Fuel > 0.f;
		}
	}
}

void ASubjectZero::OnJumpRelease()
{
	Jumping = false;
	JetpackActive = false;
	JetpackActiveTime = 0.f;
}

void ASubjectZero::OnSprintPress()
{
	Sprinting = true;
}

void ASubjectZero::OnSprintRelease()
{
	Sprinting = false;
}

void ASubjectZero::JetpackBurst()
{
	// Create a vector that represents the movement of the character within the world
	FVector Force;
	JetpackClimbSpeed = 110000;
	const FVector Direction = FVector(0.f, 0.f, 1.f);
	Force = FVector(0.f, 0.f, JetpackClimbSpeed * (0.9 + (JetpackActiveTime / (JetpackActiveTime + 50))));
	GetCharacterMovement()->AddForce(Force);
	DepleteJetpack();
}

void ASubjectZero::DepleteJetpack() 
{
	Fuel = Fuel - FuelUsage * Time;
}

float ASubjectZero::GetSpeed() const
{
	return GetVelocity().Size();
}

float ASubjectZero::GetVerticalSpeed() const
{
	return GetVelocity().Z;
}

float ASubjectZero::GetMaxHealth()
{
	return MaxHealth;
}

float ASubjectZero::GetHealth()
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

void ASubjectZero::ApplyAirResistance() 
{
	FVector Force;
	float Magnitude = Velocity.Size();
	FVector Direction =  -1.f * Velocity.GetSafeNormal();
	Force = Direction * (Magnitude * Magnitude) * AirResistanceConstant;
	GetCharacterMovement()->AddForce(Force);
}

void ASubjectZero::Log(FString msg)
{
	if (GEngine && LogsOn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, msg);
	}
}