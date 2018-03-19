// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Classes/SubjectZero.h"
#include "UnrealNetwork.h"
#include "HitscanWeapon.h"
#include "Railgun.h"
#include "Shotgun.h"
#include "Deathmatch.h"
#include "Inventory.h"
#include "ItemWeapon.h"
#include "ItemWeaponShotgun.h"
#include "ItemWeaponRailgun.h"
#include "ItemWeaponLightningGun.h"
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

	if(IsLocallyControlled() || Role == ROLE_Authority)
	{
		// For some reason you have to add the second argument (naming the UObject) in order to prevent null pointers
		// https://answers.unrealengine.com/questions/410789/tarray-of-uobjects-getting-garbage-collected.html 
		Inventory = NewObject<UInventory>(this,"I");
		UItem * LightningGun = NewObject<UItemWeaponLightningGun>(this, "DONT");
		UItem * Railgun = NewObject<UItemWeaponRailgun>(this, "GET");
		UItem * Shotgun = NewObject<UItemWeaponShotgun>(this, "IT");
		Inventory->AddItem(LightningGun);
		Inventory->AddItem(Railgun);
		Inventory->AddItem(Shotgun);
	}
}

// Called every frame
void ASubjectZero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Time = DeltaTime;

	Update();
	CalculateMovement();

	if(Grounded)
	{
		if(Jumping)
		{
			Jump();
		}
		else
		{
			Move();
		}
	}
	else
	{
		if(TryJetpack && Fuel > 0.f && Movement != FVector::ZeroVector)
		{
			Movement.Z = Jumping;
			Jetpack();
		}
		else
		{
			Move();
		}
		ApplyAirResistance();
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
	DOREPLIFETIME_CONDITION(ASubjectZero, Pitch, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, EquippedItemID, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, IsTriggerPulled, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, Crouching, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, AimDownSights, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, JetpackUsed, COND_SimulatedOnly)
}

void ASubjectZero::Move()
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

	// Only move the character if you are locally controlling it (AddMovementInput takes care of networking)
	if(IsLocallyControlled())
	{
		// Move the character on the ground
		FVector GroundMove = Movement;
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0;
		GroundMove.Z = 0.f;

		if(Grounded)
		{
			AddMovementInput(Rotation.RotateVector(GroundMove.GetSafeNormal()), 1.f);
		}
		else
		{
			AddMovementInput(Rotation.RotateVector(GroundMove.GetSafeNormal()), NormalAirControl);
		}
	}
}

void ASubjectZero::Update()
{
	Grounded = !GetCharacterMovement()->IsFalling();
	Velocity = GetVelocity();
	JetpackUsed = false;

	TryJetpack = TryJetpack && !Grounded && !AimDownSights;

	// Update pitch from controller
	if(Role == ROLE_Authority || Role == ROLE_AutonomousProxy)
	{
		Pitch = GetController()->GetControlRotation().Pitch;
	}

	if(Role == ROLE_Authority)
	{
		// Update time-sensitive states
		// Shield recharge
		if(TimeSinceTookDamage < ShieldRechargeTime)
		{
			TimeSinceTookDamage = TimeSinceTookDamage + Time;
		}
		else if(Shield < MaxShield)
		{
			Shield = FMath::Min(Shield + 20.f * Time, MaxShield);
		}

		// Damage boost
		if(DamageMultiplierDuration > 0.f)
		{
			DamageMultiplierDuration = DamageMultiplierDuration - Time;
			if(DamageMultiplierDuration <= 0.f)
			{
				DamageMultiplier = 1.f;
			}
		}

		// Jetpack
		TimeSinceJetpack += Time;
		if(TimeSinceJetpack > 3.f && Fuel < MaxFuel)
		{
			Fuel = FMath::Min(MaxFuel, Fuel + (FuelOverTime * Time));
		}

		// Update pitch of camera (which is the anchor of equipped weapon)
		FRotator NewRotation = Camera->RelativeRotation;
		NewRotation.Pitch = Pitch;
		Camera->SetRelativeRotation(NewRotation);
	}
}

//Equips local controller with a weapon, and sends information to the server
void ASubjectZero::Equip(int Slot)
{
	// Make sure the inventory actually has an item in this slot before equipping it
	if(Inventory && Inventory->CheckItem(Slot))
	{
		// Get the item from the inventory
		UItem * NewItem = Inventory->GetItem(Slot);

		// Destroy the current weapon before creating a new one
		if(Weapon)
		{
			Weapon->Destroy();
		}

		// Update replicated variable from the server so simulated proxies are updated with new equipped item
		if(HasAuthority())
		{
			Logger::Log("Updating simulated proxy item id");
			EquippedItemID = NewItem->GetItemID();
		}

		// Update the local controller and server copy with the new weapon
		if(IsLocallyControlled() || HasAuthority())
		{
			// Check if the Item is a Weapon (TODO: This should be generalized to "EquippableItem")
			if(UItemWeapon * ItemWeapon = Cast<UItemWeapon>(Inventory->GetItem(Slot)))
			{
				// Get the Actor class that represents the Item
				if(TSubclassOf<class AActor> ActorClass = GetActorFromItemID(NewItem->GetItemID()))
				{
					// Spawn the actor in the world, set the item associated with the actor to the item from the inventory
					if(GetWorld())
					{
						Weapon = GetWorld()->SpawnActor<AHitscanWeapon>(ActorClass);
						if(Weapon)
						{
							Weapon->SetItem(ItemWeapon);
						}
						else
						{
							Logger::Log("Weapon was not successfully spawned");
						}
					}
				}
				else
				{
					Logger::Log("Could not get actor class from item id " + NewItem->GetItemID().ToString());
				}
			}
			else
			{
				Logger::Log("Could not find or cast Item to ItemWeapon ");
			}
		}
	}
	else
	{
		Logger::Error("No item in slot " + FString::FromInt(Slot));
	}

	if(Weapon)
	{
		// If this actor is controlled by the local client or the server, attach the weapon to the first person mesh
		if(Role == ROLE_AutonomousProxy || Role == ROLE_Authority)
		{
			// Attach the weapon to the actor's third person mesh if the actor is not controlled by the local player, but another player
			Weapon->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("TriggerFinger"));

			// Make who is considered the shooter to be this character
			Weapon->SetShooter(this);
		}
	}
}

void ASubjectZero::Server_Equip_Implementation(int Slot)
{
	Equip(Slot);
}


bool ASubjectZero::Server_Equip_Validate(int Slot)
{
	return true;
}

void ASubjectZero::OnRep_Equip()
{
	Logger::Log("Simulated proxy update weapon");
	// Destroy the current weapon before creating a new one
	if(Weapon)
	{
		Weapon->Destroy();
	}

	if(TSubclassOf<class AActor> ActorClass = GetActorFromItemID(EquippedItemID))
	{
		if(GetWorld())
		{
			Weapon = GetWorld()->SpawnActor<AHitscanWeapon>(ActorClass);

			if(Weapon)
			{
				Weapon->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("TriggerFinger"));
				Weapon->SetShooter(this);
			}
		}
		else
		{
			Logger::Log("WHAT IN THE ACTUAL FUCK");
		}
	}
	else
	{
		Logger::Log("Could not spawn actor on simulated proxy: " + EquippedItemID.ToString());
	}
}

void ASubjectZero::Jetpack()
{
	if(IsLocallyControlled() || Role == ROLE_Authority)
	{
		if(Fuel > 0.f)
		{
			FRotator Rotation = Controller->GetControlRotation();
			Rotation.Pitch = 0;

			FVector RotatedMovement = Rotation.RotateVector(Movement);

			// Create a vector that represents the movement of the character within the world
			FVector Force = FVector(RotatedMovement.X * JetpackAcceleration * 0.5f, RotatedMovement.Y * JetpackAcceleration * 0.5f, RotatedMovement.Z != 0.f ? JetpackAcceleration : 0.f);
			Force = Force * (Sprinting ? 2.f : 1.f);
			Force = Force * Time;

			GetCharacterMovement()->Velocity += Force;

			float FuelUsed = FuelUsage * Time * ((RotatedMovement.X != 0.f ? 1.f : 0.f) + (RotatedMovement.Y != 0.f ? 1.f : 0.f) + (RotatedMovement.Z != 0.f ? 1.f : 0.f)) * (Sprinting ? 3.f : 1.f);

			if(FuelUsed > 0.f)
			{
				TimeSinceJetpack = 0.f;
				JetpackUsed = true;
			}

			if(Role == ROLE_Authority)
			{
				Fuel = FMath::Max(0.f, Fuel - (FuelUsed));
			}
		}
	}
}

void ASubjectZero::ApplyAirResistance()
{
	if(IsLocallyControlled() || Role == ROLE_Authority)
	{
		float Magnitude = Velocity.Size();
		FVector Direction = Velocity.GetSafeNormal();
		FVector Force = -1.f * Direction * (Magnitude * Magnitude) * AirResistanceConstant * Time;
		GetCharacterMovement()->Velocity += Force;
	}
}

bool ASubjectZero::ReceiveDamage(float Dmg)
{
	TimeSinceTookDamage = 0.f;
	if(HasAuthority())
	{
		if(Shield > 0.f)
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
				return ReceiveDamage(Dmg);
			}
		}
		else if(Armor > 0.f)
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
				return ReceiveDamage(Dmg);
			}
		}
		else if(Health > 0.f)
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
		else
		{
			return true;
		}
	}
	else
	{
		return false;
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
	Destroy();
}

void ASubjectZero::Destroyed()
{
	if(Weapon) Weapon->Destroy();
	Super::Destroyed();
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

void ASubjectZero::SetYaw(float Set)
{
	AddControllerYawInput(GetWorld()->GetDeltaSeconds() * Set);
}

void ASubjectZero::ServerSetYaw_Implementation(float Set)
{

}

bool ASubjectZero::ServerSetYaw_Validate(float Set)
{
	return true;
}

void ASubjectZero::SetPitch(float Set)
{
	AddControllerPitchInput(GetWorld()->GetDeltaSeconds() * Set);
	if(Role == ROLE_AutonomousProxy && IsLocallyControlled())
	{
		//ServerSetPitch(Controller->GetControlRotation().Pitch);
	}
}

void ASubjectZero::ServerSetPitch_Implementation(float NewPitch)
{
	FRotator NewRotation = Controller->GetControlRotation();
	NewRotation.Pitch = NewPitch;
	Controller->SetControlRotation(NewRotation);
	Pitch = NewPitch;
}

bool ASubjectZero::ServerSetPitch_Validate(float NewPitch)
{
	return true;
}

void ASubjectZero::SetCrouch(bool Set)
{
	if(Role == ROLE_AutonomousProxy && IsLocallyControlled())
	{
		ServerSetCrouch(Set);
	}
	Crouching = Set;
}

void ASubjectZero::ServerSetCrouch_Implementation(bool Set)
{
	SetCrouch(Set);
}

bool ASubjectZero::ServerSetCrouch_Validate(bool Set)
{
	return true;
}

void ASubjectZero::SetSprint(bool Set)
{
	if(Role == ROLE_AutonomousProxy && IsLocallyControlled())
	{
		ServerSetSprint(Set);
	}
	Sprinting = Set;
}

void ASubjectZero::ServerSetSprint_Implementation(bool Set)
{
	SetSprint(Set);
}

bool ASubjectZero::ServerSetSprint_Validate(bool Set)
{
	return true;
}

void ASubjectZero::SetJump(bool Set)
{
	if(Role == ROLE_AutonomousProxy && IsLocallyControlled())
	{
		ServerSetJump(Set);
	}
	Jumping = Set;
	if(!Grounded && Jumping)
	{
		TryJetpack = true;
	}
}

void ASubjectZero::ServerSetJump_Implementation(bool Set)
{
	SetJump(Set);
}

bool ASubjectZero::ServerSetJump_Validate(bool Set)
{
	return true;
}

void ASubjectZero::SetMoveLeft(bool Set)
{
	if(Role == ROLE_AutonomousProxy && IsLocallyControlled())
	{
		ServerSetMoveLeft(Set);
	}
	Left = Set;
}

void ASubjectZero::ServerSetMoveLeft_Implementation(bool Set)
{
	SetMoveLeft(Set);
}

bool ASubjectZero::ServerSetMoveLeft_Validate(bool Set)
{
	return true;
}

void ASubjectZero::SetMoveRight(bool Set)
{
	if(Role == ROLE_AutonomousProxy && IsLocallyControlled())
	{
		ServerSetMoveRight(Set);
	}
	Right = Set;
}

void ASubjectZero::ServerSetMoveRight_Implementation(bool Set)
{
	SetMoveRight(Set);
}

bool ASubjectZero::ServerSetMoveRight_Validate(bool Set)
{
	return true;
}

void ASubjectZero::SetMoveForward(bool Set)
{
	if(Role == ROLE_AutonomousProxy && IsLocallyControlled())
	{
		ServerSetMoveForward(Set);
	}
	Forward = Set;
}

void ASubjectZero::ServerSetMoveForward_Implementation(bool Set)
{
	SetMoveForward(Set);
}

bool ASubjectZero::ServerSetMoveForward_Validate(bool Set)
{
	return true;
}

void ASubjectZero::SetMoveBackward(bool Set)
{
	if(Role == ROLE_AutonomousProxy && IsLocallyControlled())
	{
		ServerSetMoveBackward(Set);
	}
	Backward = Set;
}

void ASubjectZero::ServerSetMoveBackward_Implementation(bool Set)
{
	SetMoveBackward(Set);
}

bool ASubjectZero::ServerSetMoveBackward_Validate(bool Set)
{
	return true;
}

void ASubjectZero::SetFire(bool Set)
{
	if(Role == ROLE_AutonomousProxy && IsLocallyControlled())
	{
		ServerSetFire(Set);
	}
	IsTriggerPulled = Set;
}

void ASubjectZero::ServerSetFire_Implementation(bool Set)
{
	SetFire(Set);
}

bool ASubjectZero::ServerSetFire_Validate(bool Set)
{
	return true;
}

void ASubjectZero::SetSecondaryFire(bool Set)
{
	if(Role == ROLE_AutonomousProxy && IsLocallyControlled())
	{
		ServerSetSecondaryFire(Set);
	}
	AimDownSights = Set;
}

void ASubjectZero::ServerSetSecondaryFire_Implementation(bool Set)
{
	SetSecondaryFire(Set);
}

bool ASubjectZero::ServerSetSecondaryFire_Validate(bool Set)
{
	return true;
}

void ASubjectZero::SetUse(bool Set)
{

}

void ASubjectZero::ServerSetUse_Implementation(bool Set)
{
	SetUse(Set);
}

bool ASubjectZero::ServerSetUse_Validate(bool Set)
{
	return true;
}

void ASubjectZero::Slot0()
{
	int ID = 0;
	Equip(ID);
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Equip(ID);
	}
}

void ASubjectZero::Slot1()
{
	int ID = 1;
	Equip(ID);
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Equip(ID);
	}
}


void ASubjectZero::Slot2()
{
	int ID = 2;
	Equip(ID);
	if(Role == ROLE_AutonomousProxy)
	{
		Server_Equip(ID);
	}
}

void ASubjectZero::Slot3()
{

}

void ASubjectZero::CalculateMovement()
{
	if(Role == ROLE_Authority || Role == ROLE_AutonomousProxy)
	{
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
		Movement.Z = Jumping ? 1.f : 0.f;
	}
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
float ASubjectZero::GetPitch() const { return Pitch; }
bool ASubjectZero::IsJetpackUsed() const { return JetpackUsed; }
bool ASubjectZero::IsJetpackActive() const { return TryJetpack; }
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