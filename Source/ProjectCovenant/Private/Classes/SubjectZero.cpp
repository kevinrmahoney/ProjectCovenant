// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Classes/SubjectZero.h"
#include "UnrealNetwork.h"
#include "HitscanWeapon.h"
#include "Railgun.h"
#include "Shotgun.h"
#include "Deathmatch.h"
#include "ProjectCovenantInstance.h"


// Sets default values
ASubjectZero::ASubjectZero(const FObjectInitializer& ObjectInitializer)
{
	// Create a CameraComponent 
	Camera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	Camera->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	// Position the camera a bit above the eyes
	Camera->RelativeLocation = FVector(0.f, 0, StandingHeight);
	// Allow the pawn to control rotation
	Camera->bUsePawnControlRotation = true;

	// Mesh
	FirstPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);         // only the owning player will see this mesh
	FirstPersonMesh->AttachToComponent(Camera, FAttachmentTransformRules::KeepRelativeTransform);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASubjectZero::BeginPlay()
{
	Super::BeginPlay();

	// Set initial character movement characteristics
	GetCharacterMovement()->MaxWalkSpeed = StandingRunSpeed;
	GetCharacterMovement()->AirControl = NormalAirControl;
	GetCharacterMovement()->MaxAcceleration = GroundAcceleration;
	GetCharacterMovement()->GravityScale = 1.f;
	GetCharacterMovement()->JumpZVelocity = JumpSpeed;
	GetCharacterMovement()->GetPhysicsVolume()->TerminalVelocity = 10000.f;

	FirstPersonMesh->SetRelativeLocation(HipfireLocation);
	FirstPersonMesh->SetRelativeRotation(HipfireRotation);
}

// Called every frame
void ASubjectZero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Time = DeltaTime;

	if(HasAuthority())
	{
		if(TimeSinceTookDamage < ShieldRechargeTime)
		{
			TimeSinceTookDamage = TimeSinceTookDamage + DeltaTime;
		}
		else if(Shield < MaxShield)
		{
			Shield = FMath::Min(Shield + 20.f * DeltaTime, MaxShield);
		}
	}

	// Update damage boost
	if(DamageMultiplierDuration > 0.f)
	{
		DamageMultiplierDuration = DamageMultiplierDuration - DeltaTime;
		if(DamageMultiplierDuration <= 0.f)
		{
			DamageMultiplier = 1.f;
		}
	}

	// Update if the character is grounded and its velocity, and update jetpack status
	if(IsLocallyControlled())
	{
		Grounded = !GetCharacterMovement()->IsFalling();
		Velocity = GetVelocity();

		if(Grounded || AimDownSights)
		{
			JetpackActive = false;
		}
	}

	// Move characters/update trigger status/aim down sights
	if(Role == ROLE_AutonomousProxy || Role == ROLE_Authority)
	{
		Move(Movement, Jumping, Sprinting, Crouching, JetpackActive, IsTriggerPulled, Controller->GetControlRotation().Pitch, AimDownSights);
		// Add passive fuel if its been long enough
		TimeSinceJetpack += DeltaTime;

		if(TimeSinceJetpack > 3.f && Fuel < MaxFuel)
		{
			Fuel = FMath::Min(MaxFuel, Fuel + (FuelUsage * 1.5f * DeltaTime));
		}
	}
	else
	{
		Move(FVector::ZeroVector, false, false, Crouching, false, IsTriggerPulled, 0.f, AimDownSights);
	}
}

void ASubjectZero::BeginDestroy() 
{
	if(Weapon) Weapon->Destroy();
	Super::BeginDestroy();
}

void ASubjectZero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	// The follow variables are replicated from server to the clients
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASubjectZero, Health)
	DOREPLIFETIME(ASubjectZero, Armor)
	DOREPLIFETIME(ASubjectZero, Shield)
	DOREPLIFETIME(ASubjectZero, Fuel)
	DOREPLIFETIME_CONDITION(ASubjectZero, Equipped, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, IsTriggerPulled, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, Crouching, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, AimDownSights, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, JetpackUsed, COND_SimulatedOnly)
}

void ASubjectZero::Move(FVector Client_Movement, bool Client_Jump, bool Client_Sprinting, bool Client_Crouching, bool Client_Jetpack, bool Client_Shooting, float Client_Pitch, bool Client_AimDownSights)
{
	// Update if the character is grounded and its velocity
	Grounded = !GetCharacterMovement()->IsFalling();
	Velocity = GetVelocity();

	JetpackUsed = false;

	if(IsLocallyControlled() || Role == ROLE_Authority)
	{
		if(Grounded)
		{
			// Update movement speeds depending on the character's stance
			if(Sprinting && !Crouching)
			{
				GetCharacterMovement()->MaxWalkSpeed = StandingSprintSpeed;
			}
			else if(Sprinting && Crouching)
			{
				GetCharacterMovement()->MaxWalkSpeed = CrouchingSprintSpeed;
			}
			else if(!Sprinting && Crouching)
			{
				GetCharacterMovement()->MaxWalkSpeed = CrouchingRunSpeed;
			}
			else
			{
				GetCharacterMovement()->MaxWalkSpeed = StandingRunSpeed;
			}

			if(AimDownSights)
			{
				GetCharacterMovement()->MaxWalkSpeed = AimDownSightsSpeed;
			}

			// Jump if commanded
			if(Controller)
			{
				// Move the character on the ground
				FRotator Rotation = Controller->GetControlRotation();
				Rotation.Pitch = 0;

				Movement.Z = 0.f;
				AddMovementInput(Rotation.RotateVector(Movement.GetSafeNormal()), 1.f);
				if(Jumping)
				{
					Jump();
				}
			}
		}
		else
		{
			// Jetpack can only be activated if it has enough fuel
			if(JetpackActive && Fuel > 0.f)
			{
				JetpackBurst();
			}
			// Strafe in the air
			else
			{
				if(Controller)
				{
					FRotator Rotation = Controller->GetControlRotation();
					Rotation.Pitch = 0;

					Movement.Z = 0.f;
					AddMovementInput(Rotation.RotateVector(Movement.GetSafeNormal()), 1.f);
				}
			}
			// Apply the force of the air if midair
			ApplyAirResistance();
		}
	}

	PlayJetpackSound();
	if(Crouching)
	{
		Camera->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		Camera->SetRelativeLocation(FVector(0.f, 0, CrouchingHeight));
		GetCapsuleComponent()->SetCapsuleHalfHeight(66.f);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -66.f));
	}
	else
	{
		Camera->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		Camera->SetRelativeLocation(FVector(0.f, 0, StandingHeight));
		GetCapsuleComponent()->SetCapsuleHalfHeight(88.f);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	}

	// Set the trigger as pulled or not pulled
	if(Weapon)
	{
		Weapon->SetTrigger(IsTriggerPulled);
		if(FirstPersonMesh)
		{
			if(AimDownSights)
			{
				FirstPersonMesh->SetRelativeLocation(Weapon->GetAimDownSightsLocation());
				FirstPersonMesh->SetRelativeRotation(Weapon->GetAimDownSightsRotation());
			}
			else
			{
				FirstPersonMesh->SetRelativeLocation(Weapon->GetHipFireLocation());
				FirstPersonMesh->SetRelativeRotation(Weapon->GetHipFireRotation());
			}
		}
	}
}

void ASubjectZero::Server_Move_Implementation(FVector Client_Movement, bool Client_Jump, bool Client_Sprinting, bool Client_Crouching, bool Client_Jetpack, bool Client_Shooting, float Client_Pitch, bool Client_AimDownSights)
{
	Movement = Client_Movement;
	Jumping = Client_Jump;
	Sprinting = Client_Sprinting;
	Crouching = Client_Crouching;
	JetpackActive = Client_Jetpack;
	IsTriggerPulled = Client_Shooting;
	Camera->RelativeRotation.Pitch = Client_Pitch;
	AimDownSights = Client_AimDownSights;
}

bool ASubjectZero::Server_Move_Validate(FVector Client_Movement, bool Client_Jump, bool Client_Sprinting, bool Client_Crouching, bool Client_Jetpack, bool Client_Shooting, float Client_Pitch, bool Client_AimDownSights)
{
	return true;
}

void ASubjectZero::Equip(int Num)
{
	if(Weapon)
	{
		Weapon->Destroy();
	}

	if(HasAuthority())
	{
		Equipped = Num;
	}

	if(Num == 0)
	{
		Weapon = GetWorld()->SpawnActor<AHitscanWeapon>(HitscanWeaponBlueprint);
	}
	else if(Num == 1)
	{
		Weapon = GetWorld()->SpawnActor<ARailgun>(RailgunBlueprint);
	}
	else if(Num == 2)
	{
		Weapon = GetWorld()->SpawnActor<AShotgun>(ShotgunBlueprint);
	}

	if(Weapon)
	{
		// If this actor is controlled by the local client or the server, attach the weapon to the first person mesh
		if(Role == ROLE_AutonomousProxy || Role == ROLE_Authority)
		{
			// Attach the weapon to the actor's third person mesh if the actor is not controlled by the local player, but another player
			Weapon->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("TriggerFinger"));
		}
		// If this actor is controlled by a remote client or server, attach to the third person mesh
		else
		{
			Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("TriggerFinger"));
		}

		// Make who is considered the shooter to be this character
		Weapon->SetShooter(this);
	}
}

void ASubjectZero::Server_Equip_Implementation(int Num)
{
	Equip(Num);
}

void ASubjectZero::OnRep_Equip()
{
	if(Role == ROLE_SimulatedProxy)
	{
		Equip(Equipped);
	}
}

bool ASubjectZero::Server_Equip_Validate(int Num)
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
		Force = Force * (Sprinting ? 2.f : 1.f);

		GetCharacterMovement()->Velocity += Force * Time;

		float FuelUsed = FuelUsage * ((Movement.X != 0.f ? 1.f : 0.f) + (Movement.Y != 0.f ? 1.f : 0.f) + (Jumping ? 1.f : 0.f)) * (Sprinting ? 3.f : 1.f);
		if(FuelUsed > 0.f)
		{
			TimeSinceJetpack = 0.f;
			JetpackUsed = true;
		}
		Fuel = FMath::Max(0.f, Fuel - (FuelUsed * Time));
	}
}

void ASubjectZero::ApplyAirResistance()
{
	FVector Force;
	float Magnitude = Velocity.Size();
	FVector Direction = -1.f * Velocity.GetSafeNormal();
	Force = Direction * (Magnitude * Magnitude) * AirResistanceConstant;
	GetCharacterMovement()->Velocity += Force * Time;
}

bool ASubjectZero::ReceiveDamage(float Dmg)
{
	TimeSinceTookDamage = 0.f;
	if(HasAuthority())
	{
		if(Shield != 0.f)
		{
			if(Shield > Dmg)
			{
				Shield = Shield - Dmg;
				return false;
			}
			else
			{
				Dmg = Dmg - Shield;
				Shield = 0.f;
				ReceiveDamage(Dmg);
			}
		}
		else if(Armor != 0.f)
		{
			if(Armor > Dmg)
			{
				Armor = Armor - Dmg;
				return false;
			}
			else
			{
				Dmg = Dmg - Armor;
				Armor = 0.f;
				ReceiveDamage(Dmg);
			}
		}
		else if(Health != 0.f)
		{
			if(Health > Dmg)
			{
				Health = Health - Dmg;
				return false;
			}
			else
			{
				Health = 0.f;
				return true;
			}
		}
	}
	return false;
}

bool ASubjectZero::ReceiveDamageOverTime(float DamageAmount, bool Overlapped) {
	
	return true;
}

void ASubjectZero::Kill()
{
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	if(Weapon)
	{
		Weapon->Destroy();
	}
	Super::Destroy();
}

void ASubjectZero::Destroyed()
{
	if(Weapon) Weapon->Destroy();
	Super::Destroyed();
}

void ASubjectZero::SetYaw(float Set)
{
	AddControllerYawInput(GetWorld()->GetDeltaSeconds() * Set);
}

void ASubjectZero::IncreaseHealth(float amount) {
	Health = FMath::Min(Health + MaxHealth * amount, MaxHealth);
}

void ASubjectZero::IncreaseArmor(float amount) {
	Armor = FMath::Min(Armor + MaxArmor * amount, MaxArmor);
}

void ASubjectZero::IncreaseFuel(float amount) {
	Fuel = FMath::Min(Fuel + MaxFuel * amount, MaxFuel);
}

void ASubjectZero::DamageBoost(float BoostMultiplier, float BoostDuration)
{
	DamageMultiplier = BoostMultiplier;
	DamageMultiplierDuration = BoostDuration;
}

void ASubjectZero::SetPitch(float Set)
{
	AddControllerPitchInput(GetWorld()->GetDeltaSeconds() * Set);
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Move(Movement, Jumping, Sprinting, Crouching, JetpackActive, IsTriggerPulled, Controller->GetControlRotation().Pitch, AimDownSights);
	}
}

void ASubjectZero::SetCrouch(bool Set)
{
	Crouching = Set;
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Move(Movement, Jumping, Sprinting, Crouching, JetpackActive, IsTriggerPulled, Controller->GetControlRotation().Pitch, AimDownSights);
	}
}

void ASubjectZero::SetSprint(bool Set)
{
	Sprinting = Set;
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Move(Movement, Jumping, Sprinting, Crouching, JetpackActive, IsTriggerPulled, Controller->GetControlRotation().Pitch, AimDownSights);
	}
}

void ASubjectZero::SetJump(bool Set)
{
	Jumping = Set;
	if(!Grounded && Jumping)
	{
		JetpackActive = true;
	}
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Move(Movement, Jumping, Sprinting, Crouching, JetpackActive, IsTriggerPulled, Controller->GetControlRotation().Pitch, AimDownSights);
	}
}

void ASubjectZero::SetMoveLeft(bool Set)
{
	Left = Set;
	// Process left/right movement
	if(Left && !Right)
	{
		Movement.Y = -1.f;
	}
	else if(Right && !Left)
	{
		Movement.Y = 1.f;
	}
	else
	{
		Movement.Y = 0.f;
	}
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Move(Movement, Jumping, Sprinting, Crouching, JetpackActive, IsTriggerPulled, Controller->GetControlRotation().Pitch, AimDownSights);
	}
}

void ASubjectZero::SetMoveRight(bool Set)
{
	Right = Set;
	// Process left/right movement
	if(Left && !Right)
	{
		Movement.Y = -1.f;
	}
	else if(Right && !Left)
	{
		Movement.Y = 1.f;
	}
	else
	{
		Movement.Y = 0.f;
	}
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Move(Movement, Jumping, Sprinting, Crouching, JetpackActive, IsTriggerPulled, Controller->GetControlRotation().Pitch, AimDownSights);
	}
}

void ASubjectZero::SetMoveForward(bool Set)
{
	Forward = Set;
	// Process forward/backward movement
	if(Backward && !Forward)
	{
		Movement.X = -1.f;
	}
	else if(Forward && !Backward)
	{
		Movement.X = 1.f;
	}
	else
	{
		Movement.X = 0.f;
	}
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Move(Movement, Jumping, Sprinting, Crouching, JetpackActive, IsTriggerPulled, Controller->GetControlRotation().Pitch, AimDownSights);
	}
}

void ASubjectZero::SetMoveBackward(bool Set)
{
	Backward = Set;
	// Process forward/backward movement
	if(Backward && !Forward)
	{
		Movement.X = -1.f;
	}
	else if(Forward && !Backward)
	{
		Movement.X = 1.f;
	}
	else
	{
		Movement.X = 0.f;
	}
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Move(Movement, Jumping, Sprinting, Crouching, JetpackActive, IsTriggerPulled, Controller->GetControlRotation().Pitch, AimDownSights);
	}
}

void ASubjectZero::SetFire(bool Set)
{
	IsTriggerPulled = Set;
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Move(Movement, Jumping, Sprinting, Crouching, JetpackActive, IsTriggerPulled, Controller->GetControlRotation().Pitch, AimDownSights);
	}
}

void ASubjectZero::SetSecondaryFire(bool Set)
{
	AimDownSights = Set;
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Move(Movement, Jumping, Sprinting, Crouching, JetpackActive, IsTriggerPulled, Controller->GetControlRotation().Pitch, AimDownSights);
	}
}

void ASubjectZero::SetUse(bool Set)
{

}

void ASubjectZero::Slot0()
{
	Equip(0);
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Equip(0);
	}
}

void ASubjectZero::Slot1()
{
	Equip(1);
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Equip(1);
	}
}


void ASubjectZero::Slot2()
{
	Equip(2);
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Equip(2);
	}
}

void ASubjectZero::Slot3()
{

}

// Getters
float ASubjectZero::GetDamageMultiplier() const { return DamageMultiplier; }
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
bool ASubjectZero::IsJetpackUsed() const { return JetpackUsed; }
bool ASubjectZero::IsJetpackActive() const { return JetpackActive; }
bool ASubjectZero::IsSprinting() const { return Sprinting; }
bool ASubjectZero::IsCrouching() const { return Crouching; }
bool ASubjectZero::IsAimingDownSights() const { return AimDownSights; }

// Getters
FName ASubjectZero::GetPlayerName() const {
	FName Name = "Unknown";
	if(AHumanController * HumanController = Cast<AHumanController>(GetController()))
	{
		if(Role == ROLE_SimulatedProxy || HasAuthority())
		{
			Name = HumanController->PlayerName;
		}
	}
	return Name;
}
