// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Classes/SubjectZero.h"
#include "Engine.h"
#include "UnrealNetwork.h"


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
	if(Grounded)
	{
		// Jump
		if(!Jumping)
		{
			JetpackActive = false;
		}
	}

	if(!HasAuthority())
	{
		Server_Move(Movement, Jumping, Sprinting, JetpackActive);
	}

	if(Controller)
	{
		if(Grounded)
		{
			GetCharacterMovement()->MaxWalkSpeed = Sprinting ? MaxGroundSpeed * 2.f : MaxGroundSpeed;

			if(Jumping)
			{
				Jump();
			}
			else
			{
				FRotator Rotation = Controller->GetControlRotation();
				Rotation.Pitch = 0;

				Movement.Z = 0.f;
				AddMovementInput(Rotation.RotateVector(Movement.GetSafeNormal()), 1.f);
			}
		}
		else
		{
			if(JetpackActive)
			{
				JetpackBurst();
			}
			ApplyAirResistance();
		}
	}
}

void ASubjectZero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASubjectZero, Health);
	DOREPLIFETIME(ASubjectZero, Armor);
	DOREPLIFETIME(ASubjectZero, Shield);
	DOREPLIFETIME(ASubjectZero, Fuel);

}



void ASubjectZero::Server_Move_Implementation(FVector Client_Movement, bool Client_Jump, bool Client_Sprinting, bool Client_Jetpack)
{
	Movement = Client_Movement;
	Jumping = Client_Jump;
	Sprinting = Client_Sprinting;
	JetpackActive = Client_Jetpack;
}

bool ASubjectZero::Server_Move_Validate(FVector Movement, bool Jump, bool Sprinting, bool Jetpack)
{
	return true;
}
void ASubjectZero::JetpackBurst()
{
	if(Controller)
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0;

		FVector RotatedMovement = Rotation.RotateVector(Movement);

		// Create a vector that represents the movement of the character within the world
		FVector Force = FVector(RotatedMovement.X * JetpackAcceleration * 0.5f, RotatedMovement.Y * JetpackAcceleration * 0.5f, Jumping ? JetpackAcceleration : 0.f);
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

void ASubjectZero::Server_Shoot_Implementation()
{
	float Length = 100000.f;
	float Height = 63.f;
	float Damage = 10.f;
	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = GetActorLocation() + FVector(0.f, 0.f, Height);
	FVector ForwardVector = Controller->GetControlRotation().Vector();
	FVector EndTrace = StartTrace + (ForwardVector * Length);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(this);

	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 1.f);
	if(GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Pawn, *TraceParams))
	{
		if(HitResult)
		{
			if((HitResult->GetActor()))
			{
				ASubjectZero * Victim = Cast<ASubjectZero>(HitResult->GetActor());
				if(Victim)
				{
					Log("Player " + GetName() + " hit " + Victim->GetName() + " for " + FString::SanitizeFloat(Damage) + " damage!");
					Victim->TakeDamage(10.f);
				}
				else
				{
					Log("No hit!");
				}
			}
		}
	}

	delete HitResult;
	delete TraceParams;
}

bool ASubjectZero::Server_Shoot_Validate()
{
	return true;
}

void ASubjectZero::TakeDamage(float Damage)
{
	if(Shield != 0.f)
	{
		if(Shield > Damage)
		{
			Shield = Shield - Damage;
			Log(FString::SanitizeFloat(Shield));
			return;
		}
		else
		{
			Shield = 0.f;
			Damage = Damage - Shield;
			TakeDamage(Damage);
			return;
		}
	}

	if(Armor != 0.f)
	{
		if(Armor > Damage)
		{
			Armor = Armor - Damage;
			return;
		}
		else
		{
			Armor = 0.f;
			Damage = Damage - Armor;
			TakeDamage(Damage);
			return;
		}
	}

	if(Health != 0.f)
	{
		if(Health > Damage)
		{
			Health = Health - Damage;
			return;
		}
		else
		{
			Health = 0.f;
			Log("Player died!");
			Shield = MaxShield;
			Armor = MaxArmor;
			Health = MaxHealth;
			TakeDamage(Damage);
			return;
		}
	}
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
	Input->BindAction("Shoot", IE_Pressed, this, &ASubjectZero::InputShootPress);
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

void ASubjectZero::InputShootPress()
{
	Server_Shoot();
}

void ASubjectZero::Join(FString IPAddress)
{
	Log("Joining server " + IPAddress);
}

void ASubjectZero::Host()
{
	Log("Hosting server");
}

void ASubjectZero::Map(FString Map)
{
	Log("Changing map to " + Map);
}


void ASubjectZero::Log(FString msg)
{
	if (GEngine && LogsOn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, msg);
	}
}