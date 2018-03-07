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

	// Update if the character is grounded and its velocity
	Grounded = !GetCharacterMovement()->IsFalling();
	Velocity = GetVelocity();

	// If the character is locally controlled, process the input coming from the controller
	if(IsLocallyControlled())
	{
		if(Grounded || AimDownSights)
		{
			JetpackActive = false;
		}

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
		Move(Movement, Jumping, Sprinting, Crouching, JetpackActive, IsTriggerPulled, Controller->GetControlRotation().Pitch, AimDownSights);
	}

	// Add passive fuel if its been long enough
	TimeSinceJetpack += DeltaTime;
	if(TimeSinceJetpack > 3.f && Fuel < MaxFuel)
	{
		Fuel = FMath::Min(MaxFuel, Fuel + (FuelUsage * 1.5f * DeltaTime));
	}
}

void ASubjectZero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	// The follow variables are replicated from server to the clients
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASubjectZero, Health)
	DOREPLIFETIME(ASubjectZero, Armor)
	DOREPLIFETIME(ASubjectZero, Shield)
	DOREPLIFETIME(ASubjectZero, Fuel)
}

void ASubjectZero::Move(FVector Client_Movement, bool Client_Jump, bool Client_Sprinting, bool Client_Crouching, bool Client_Jetpack, bool Client_Shooting, float Client_Pitch, bool Client_AimDownSights)
{
	// Update if the character is grounded and its velocity
	Grounded = !GetCharacterMovement()->IsFalling();
	Velocity = GetVelocity();

	if(Controller)
	{
		if(Grounded)
		{
			// Move the character on the ground
			FRotator Rotation = Controller->GetControlRotation();
			Rotation.Pitch = 0;

			Movement.Z = 0.f;
			AddMovementInput(Rotation.RotateVector(Movement.GetSafeNormal()), 1.f);
		}
		else
		{
			FRotator Rotation = Controller->GetControlRotation();
			Rotation.Pitch = 0;

			Movement.Z = 0.f;
			AddMovementInput(Rotation.RotateVector(Movement.GetSafeNormal()), 1.f);
		}
	}

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
		if(Jumping) Jump();

	}
	else
	{
		// Activated the jetpack 
		if(JetpackActive)
		{
			JetpackBurst();
		}
		// Strafe in the air

		// Apply the force of the air if midair
		ApplyAirResistance();
	}

	// Jetpack can only be activated if it has enough fuel
	JetpackActive = JetpackActive && Fuel > 0.f;

	// Set the trigger as pulled or not pulled
	if(Weapon)
	{
		Weapon->SetTrigger(IsTriggerPulled);
		if(AimDownSights)
		{
			FirstPersonMesh->SetRelativeLocation(Weapon->GetAimDownSightsLocation());
			FirstPersonMesh->SetRelativeRotation(Weapon->GetAimDownSightsRotation());
		}
		else
		{
			FirstPersonMesh->SetRelativeLocation(HipfireLocation);
			FirstPersonMesh->SetRelativeRotation(HipfireRotation);
		}
	}
}

void ASubjectZero::Server_Move_Implementation(FVector Client_Movement, bool Client_Jump, bool Client_Sprinting, bool Client_Crouching, bool Client_Jetpack, bool Client_Shooting, float Client_Pitch, bool Client_AimDownSights)
{
	//Movement = Client_Movement;
	//Jumping = Client_Jump;
	//Sprinting = Client_Sprinting;
	//Crouching = Client_Crouching;
	//JetpackActive = Client_Jetpack;
	//IsTriggerPulled = Client_Shooting;
	//Camera->RelativeRotation.Pitch = Client_Pitch;
	//AimDownSights = Client_AimDownSights;
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
		if(IsLocallyControlled() || Role == ROLE_Authority)
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

		GetCharacterMovement()->AddForce(Force);


		float FuelUsed = FuelUsage * ((Movement.X != 0.f ? 1.f : 0.f) + (Movement.Y != 0.f ? 1.f : 0.f) + (Jumping ? 1.f : 0.f)) * (Sprinting ? 3.f : 1.f);
		if(FuelUsed > 0.f) TimeSinceJetpack = 0.f;
		Fuel = FMath::Max(0.f, Fuel - (FuelUsed * Time));
	}
}

void ASubjectZero::ApplyAirResistance()
{
	FVector Force;
	float Magnitude = Velocity.Size();
	FVector Direction = -1.f * Velocity.GetSafeNormal();
	Force = Direction * (Magnitude * Magnitude) * AirResistanceConstant;
	GetCharacterMovement()->AddForce(Force);
}

bool ASubjectZero::ReceiveDamage(float Dmg)
{
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
				Shield = MaxShield;
				Armor = MaxArmor;
				Health = MaxHealth;
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

void ASubjectZero::SetYaw(float Set)
{
	AddControllerYawInput(GetWorld()->GetDeltaSeconds() * Set);
}

void ASubjectZero::IncreaseHealth(float amount) {
	Health += MaxHealth * amount;
}

void ASubjectZero::SetPitch(float Set)
{
	AddControllerPitchInput(GetWorld()->GetDeltaSeconds() * Set);
}

void ASubjectZero::SetCrouch(bool Set)
{
	Crouching = Set;
	if(Set)
	{
		Camera->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		Camera->AddRelativeLocation(FVector(0.f, 0, CrouchingHeight - StandingHeight));
		GetCapsuleComponent()->SetCapsuleHalfHeight(66.f);
	}
	else
	{
		Camera->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		Camera->AddRelativeLocation(FVector(0.f, 0, StandingHeight - CrouchingHeight));
		GetCapsuleComponent()->SetCapsuleHalfHeight(88.f);
	}
}

void ASubjectZero::SetSprint(bool Set)
{
	Sprinting = Set;
}

void ASubjectZero::SetJump(bool Set)
{
	if(!Grounded && !Jumping && Set)
	{
		JetpackActive = Fuel > 0.f;
	}
	Jumping = Set;
}

void ASubjectZero::SetMoveLeft(bool Set)
{
	Left = Set;
}

void ASubjectZero::SetMoveRight(bool Set)
{
	Right = Set;
}

void ASubjectZero::SetMoveForward(bool Set)
{
	Forward = Set;
}

void ASubjectZero::SetMoveBackward(bool Set)
{
	Backward = Set;
}

void ASubjectZero::SetFire(bool Set)
{
	IsTriggerPulled = Set;
}

void ASubjectZero::SetSecondaryFire(bool Set)
{
	AimDownSights = Set;
}

void ASubjectZero::SetUse(bool Set)
{

}

void ASubjectZero::Slot0()
{

	//Equip(0);
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Equip(0);
	}
	else if(Role == ROLE_Authority)
	{
		Equip(0);
	}
}

void ASubjectZero::Slot1()
{
	//Equip(1);
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Equip(1);
	}
	else if(Role == ROLE_Authority)
	{
		Equip(1);
	}
}


void ASubjectZero::Slot2()
{
	//Equip(2);
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Equip(2);
	}
	else if(Role == ROLE_Authority)
	{
		Equip(2);
	}
}

void ASubjectZero::Slot3()
{

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
