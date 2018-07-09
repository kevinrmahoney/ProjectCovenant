// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Classes/SubjectZero.h"
#include "UnrealNetwork.h"
#include "Item.h"
#include "ItemWeapon.h"
#include "Weapon.h"
#include "Railgun.h"
#include "Shotgun.h"
#include "Deathmatch.h"
#include "Inventory.h"
#include "Interactor.h"
#include "Interactable.h"
#include "BaseState.h"
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

	// Create the interactor
	Interactor = ObjectInitializer.CreateDefaultSubobject<UInteractor>(this, TEXT("Interactor"));

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

	Inventory = NewObject<UInventory>(this, "I");
}

void ASubjectZero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	// The follow variables are replicated from server to the clients
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASubjectZero, Health)
	DOREPLIFETIME(ASubjectZero, Armor)
	DOREPLIFETIME(ASubjectZero, Shield)
	DOREPLIFETIME(ASubjectZero, Fuel)
	DOREPLIFETIME(ASubjectZero, IsJetpackDisabled)
	DOREPLIFETIME_CONDITION(ASubjectZero, Pitch, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, EquippedItemID, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, IsTriggerPulled, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, Crouching, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, AimDownSights, COND_SimulatedOnly)
	DOREPLIFETIME_CONDITION(ASubjectZero, JetpackUsed, COND_SimulatedOnly)
}

void ASubjectZero::BeginDestroy()
{
	if(Weapon) Weapon->Destroy();
	Super::BeginDestroy();
}

// Called every frame
void ASubjectZero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Time = DeltaTime;

	Update();
	CalculateMovement();

	// Comment / Uncomment this when finding a weapon's aim down sights and hipfire location
	//AimDownSights = true;

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
		if(TryJetpack && Fuel > 0.f && Movement != FVector::ZeroVector && !IsJetpackDisabled)
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

	if(IsLocallyControlled())
	{
		if(AimDownSights)
		{
			Camera->FieldOfView = AimDownSightsFieldOfView;
		}
		else
		{
			Camera->FieldOfView = DefaultFieldOfView;
		}
	}

	PlayJetpackSound();
	if(Crouching)
	{
		Camera->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		Camera->SetRelativeLocation(FVector(0.f, 0, 15.f));
		GetCapsuleComponent()->SetCapsuleHalfHeight(CrouchingHeight);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -CrouchingHeight));
	}
	else
	{
		Camera->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		Camera->SetRelativeLocation(FVector(0.f, 0, 75.f));
		GetCapsuleComponent()->SetCapsuleHalfHeight(StandingHeight);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -StandingHeight));
	}
	
	// Set the trigger as pulled or not pulled

	if(Weapon)
	{
		Weapon->AimDownSights(AimDownSights);
		Weapon->SetTrigger(IsTriggerPulled);
	}
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

	if(Grounded || AimDownSights) TryJetpack = false;

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

		if(TimeSinceTookDamage > JetpackDisableTime)
		{
			IsJetpackDisabled = false;
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
	check(Inventory != nullptr)
	UItem * NewItem = Inventory->GetItem(Slot);

	if(NewItem)
	{
		if(HasAuthority())
		{
			EquippedItemID = NewItem->ItemID;
		}
		else
		{
			Server_Equip(NewItem->ItemID);
		}

		// Make sure the inventory actually has an item in this slot before equipping it
		if(Inventory->CheckItemAt(Slot))
		{
			// Destroy the current weapon before creating a new one
			if(Weapon) Weapon->Destroy();

			ABaseState * State = Cast<ABaseState>(GetWorld()->GetGameState());
			if(State)
			{
				// Get the Actor class that represents the Item
				if(TSubclassOf<class AActor> ActorClass = State->GetActorClassFromItem(NewItem))
				{
					// Spawn the actor in the world, set the item associated with the actor to the item from the inventory
					Weapon = GetWorld()->SpawnActor<AWeapon>(ActorClass);
					if(Weapon)
					{
						Weapon->SetItem(NewItem);
						Weapon->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("TriggerFinger"));
						Weapon->SetShooter(this);
					}
				}
				else
				{
					Logger::Log("Could not get actor class from item id " + NewItem->GetItemID().ToString());
				}
			}
		}
	}
}

/* Tell the server which item the client has attempted to equip
	Since inventory slots are not synced between client and server,
	the client must send the ItemID of the Slot number that has been 
	equipped, rather than the slot. If the server's inventory has the 
	Item, then it switches to it too.

	NOTE: In order to do it this way, the inventoy cannot have multiple
	instances of a single item.
*/
void ASubjectZero::Server_Equip_Implementation(FName ItemID)
{
	check(Inventory != nullptr)

	int Slot = 0;
	for(UItem * Item : Inventory->GetItems())
	{
		if(Item && Item->ItemID == ItemID)
		{
			Equip(Slot);
			return;
		}
		else
		{
			Slot++;
		}
	}
}


bool ASubjectZero::Server_Equip_Validate(FName ItemID)
{
	return true;
}

void ASubjectZero::OnRep_Equip()
{
	// Destroy the current weapon before creating a new one
	if(Weapon)
	{
		Weapon->Destroy();
	}
	ABaseState * State = Cast<ABaseState>(GetWorld()->GetGameState());
	if(State)
	{
		UItem * Item = NewObject<UItem>();
		Item->ItemID = EquippedItemID;

		if(TSubclassOf<class AActor> ActorClass = State->GetActorClassFromItem(Item))
		{
			Weapon = GetWorld()->SpawnActor<AWeapon>(ActorClass);
			if(Weapon)
			{
				Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("TriggerFinger"));
				Weapon->SetShooter(this);
			}
		}
		else
		{
			Logger::Log("Could not spawn actor on simulated proxy: " + EquippedItemID.ToString());
		}
		delete Item;
	}
}

void ASubjectZero::Jetpack()
{
	if(IsLocallyControlled() || Role == ROLE_Authority)
	{
		if(Fuel > 0.f && !IsJetpackDisabled)
		{
			FRotator Rotation = Controller->GetControlRotation();
			Rotation.Pitch = 0;

			FVector RotatedMovement = Rotation.RotateVector(Movement);

			// TODO: Lots of duplicate code here, needs refactoring (create "impulse" method to add velocity to CharacterMovement, other refactoring)
			if(Burst && Fuel > MaxFuel * 0.25f)
			{
				// Create a vector that represents the movement of the character within the world
				if(RotatedMovement == FVector(0.f, 0.f, 1.f))
				{
					RotatedMovement = FVector(0.f, 0.f, 1.f);
				}
				else
				{
					RotatedMovement.Z = 0.f;
					RotatedMovement.Normalize();
				}

				FVector Force = RotatedMovement * JetpackBurstImpulse;
				GetCharacterMovement()->Velocity += Force;

				float FuelUsed = MaxFuel * 0.25f;

				if(FuelUsed > 0.f)
				{
					TimeSinceJetpack = 0.f;
					JetpackUsed = true;
				}

				if(Role == ROLE_Authority)
				{
					Fuel = FMath::Max(0.f, Fuel - (FuelUsed));
					TryJetpack = TryJetpack && Fuel > 0.f;
				}
				Burst = false;
			}
			else
			{
				// Create a vector that represents the movement of the character within the world
				FVector Force = FVector(RotatedMovement.X * JetpackAcceleration * 0.5f, RotatedMovement.Y * JetpackAcceleration * 0.5f, RotatedMovement.Z != 0.f ? JetpackAcceleration : 0.f);
				Force = Force * Time;

				GetCharacterMovement()->Velocity += Force;

				float FuelUsed = FuelUsage * Time * ((RotatedMovement.X != 0.f ? 1.f : 0.f) + (RotatedMovement.Y != 0.f ? 1.f : 0.f) + (RotatedMovement.Z != 0.f ? 1.f : 0.f));

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

bool ASubjectZero::ReceiveDamage(float Dmg, bool SelfDamage)
{
	// Self damage doesn't disable jetpack
	IsJetpackDisabled = !SelfDamage;
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
				return ReceiveDamage(Dmg, SelfDamage);
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
				return ReceiveDamage(Dmg, SelfDamage);
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

void ASubjectZero::SetSkin(USkeletalMesh * TPMesh, USkeletalMesh * FPMesh)
{
	if(TPMesh) GetMesh()->SetSkeletalMesh(TPMesh);
	if(FPMesh) FirstPersonMesh->SetSkeletalMesh(FPMesh);

	if(TPMesh) Logger::Log("Player " + GetName() + " equipped skin " + TPMesh->GetName());
}

void ASubjectZero::Kill()
{
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	Destroy();
}

// This is called when possessed
void ASubjectZero::Restart()
{
	Super::Restart();

	// If locally controlled, request that the character be given starting weapons
	if(IsLocallyControlled())
	{
		RequestStartingInventory();
	}
}

void ASubjectZero::RequestStartingInventory()
{
	// If character has authority, ask the game mode to gave the starting inventory to this character
	if(HasAuthority())
	{
		if(ABaseMode * GameMode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->GiveStartingInventory(this);
		}
	}
	// If this character does not have authority, request it via RPC
	else if(Role == ROLE_AutonomousProxy)
	{
		ServerRequestStartingInventory();
	}
}
void ASubjectZero::ServerRequestStartingInventory_Implementation()
{
	RequestStartingInventory();
}

bool ASubjectZero::ServerRequestStartingInventory_Validate()
{
	return true;
}

// RPC to add items to the inventory of clients
void ASubjectZero::ClientAddItemToInventory_Implementation(const FItemSerialized & ItemSerialized)
{
	if(Role != ROLE_Authority)
	{
		UItem * Item = UItem::UnserializeItem(ItemSerialized);
		AddItemToInventory(Item);
	}
}

void ASubjectZero::AddItemToInventory(UItem * Item)
{
	if(Role == ROLE_Authority)
	{
		if(Inventory && Item)
		{
			// Add the item to the server's inventory
			Inventory->AddItem(Item);

			if(!IsLocallyControlled())
			{
				// Send RPC to update the client's inventory
				FItemSerialized ItemSerialized = UItem::SerializeItem(Item);
				ClientAddItemToInventory(ItemSerialized);
			}
		}
	}
	else if(Role == ROLE_AutonomousProxy)
	{
		if(Inventory && Item)
		{
			if(IsLocallyControlled())
			{
				// Add item to client's inventory
				Inventory->AddItem(Item);
			}
		}
	}

	if(AHumanController * HumanController = Cast<AHumanController>(Controller))
	{
		HumanController->UpdateHUD();
	}
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

void ASubjectZero::SetBurst(bool Set)
{
	if(Role == ROLE_AutonomousProxy && IsLocallyControlled())
	{
		ServerSetBurst(Set);
	}
	Burst = Set;
}

void ASubjectZero::ServerSetBurst_Implementation(bool Set)
{
	SetBurst(Set);
}

bool ASubjectZero::ServerSetBurst_Validate(bool Set)
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

void ASubjectZero::SetInteract(bool Set)
{
	if(Set)
	{
		AInteractable * InteractableHit = Interactor->GetInteractable();
		if(InteractableHit)
		{
			Interact(InteractableHit);
		}
	}
}

void ASubjectZero::Interact(AInteractable * InteractableHit)
{
	check(InteractableHit != nullptr)

	if(HasAuthority())
	{
		ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode());
		if(Mode)
		{
			ABaseState * State = Cast<ABaseState>(Mode->GameState);
			if(State)
			{
				Mode->GiveItemToCharacter(this, State->GetItemFromStaticMesh(InteractableHit->GetStaticMeshComponent()->GetStaticMesh()));
				InteractableHit->Destroy();
			}
		}
	}
	else
	{
		ServerInteract(InteractableHit);
	}
}


void ASubjectZero::ServerInteract_Implementation(AInteractable * InteractableHit)
{
	Interact(InteractableHit);
}

bool ASubjectZero::ServerInteract_Validate(AInteractable * Interactable)
{
	return true;
}

void ASubjectZero::Slot0()
{
	Equip(0);
}

void ASubjectZero::Slot1()
{
	Equip(1);
}


void ASubjectZero::Slot2()
{
	Equip(2);
}

void ASubjectZero::DropItem(int Index)
{
	check(Inventory != nullptr)
	Drop(Inventory->GetItem(Index));
}

void ASubjectZero::Drop(UItem * ItemToDrop)
{
	check(ItemToDrop != nullptr)
	check(Inventory != nullptr)

	if(Weapon && Weapon->GetItem() && ItemToDrop->ItemID == Weapon->GetItem()->ItemID)
	{
		Weapon->Destroy();
	}

	Inventory->RemoveItem(ItemToDrop);

	if(HasAuthority())
	{
		EquippedItemID = FName("-1");
		if(ABaseMode * Mode = Cast<ABaseMode>(GetWorld()->GetAuthGameMode()))
		{
			Mode->SpawnInteractable(ItemToDrop, Camera->GetComponentLocation() + Camera->GetForwardVector() * 300.f, GetVelocity() + Camera->GetForwardVector() * 10000.f);
		}
	}
	else
	{
		// Send RPC to update the client's inventory
		FItemSerialized ItemSerialized = UItem::SerializeItem(ItemToDrop);
		ServerDrop(ItemSerialized);
	}
}

void ASubjectZero::ServerDrop_Implementation(const FItemSerialized & ItemSerialized)
{
	Drop(UItem::UnserializeItem(ItemSerialized));
}

bool ASubjectZero::ServerDrop_Validate(const FItemSerialized & ItemSerialized)
{
	return true;
}

void ASubjectZero::AtomizeItem(int Index)
{
	check(Inventory != nullptr)
	Atomize(Inventory->GetItem(Index));
}

void ASubjectZero::Atomize(UItem * ItemToDrop)
{
	check(ItemToDrop != nullptr && Inventory != nullptr)

	if(Weapon && Weapon->GetItem() && ItemToDrop->ItemID == Weapon->GetItem()->ItemID)
	{
		Weapon->Destroy();
	}
	Inventory->RemoveItem(ItemToDrop);

	if(HasAuthority())
	{
		EquippedItemID = FName("-1");
	}
	else
	{
		ServerAtomize(UItem::SerializeItem(ItemToDrop));
	}

	delete ItemToDrop;
}

void ASubjectZero::ServerAtomize_Implementation(const FItemSerialized & ItemSerialized)
{
	Atomize(UItem::UnserializeItem(ItemSerialized));
}

bool ASubjectZero::ServerAtomize_Validate(const FItemSerialized & ItemSerialized)
{
	return true;
}

void ASubjectZero::Reload()
{
	if(!HasAuthority())
	{
		ServerReload();
	}
	if(Weapon)
	{
		Weapon->BeginReload();
	}
}

void ASubjectZero::ServerReload_Implementation()
{
	Reload();
}

bool ASubjectZero::ServerReload_Validate()
{
	return true;
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

/* RequestPreferredSkin()
	Request what the preferred skin is, as saved on each client's game instance,
	then perform an action to equip the skin
*/
void ASubjectZero::RequestPreferredSkin()
{
	// If locally controlled, then a game instance should exist
	if(IsLocallyControlled())
	{
		if(UProjectCovenantInstance * Instance = Cast<UProjectCovenantInstance>(GetGameInstance()))
		{
			SetPreferredSkin(Instance->ThirdPersonSkin, Instance->FirstPersonSkin);
		}
	}
	// If not locally controlled, send an RPC to the client requesting it
	else
	{
		ClientRequestPreferredSkin();
	}
}

/* ClientRequestPreferredSkin_Implementation()
	Request the preferred skin from the client's side
*/
void ASubjectZero::ClientRequestPreferredSkin_Implementation()
{
	if(IsLocallyControlled())
	{
		RequestPreferredSkin();
	}
}

/* SetPreferredSkin()
	Set the skin to the preferred skin taken from the client.
*/
void ASubjectZero::SetPreferredSkin(USkeletalMesh * ThirdPersonSkin, USkeletalMesh * FirstPersonSkin)
{
	// If the server, then set the skin and multicast to all clients the new skin for the character
	if(HasAuthority())
	{
		SetSkin(ThirdPersonSkin, FirstPersonSkin);
		MulticastSetPreferredSkin(ThirdPersonSkin, FirstPersonSkin);
	}
	// If not the server, tell the server to do it
	else
	{
		ServerSetPreferredSkin(ThirdPersonSkin, FirstPersonSkin);
	}
}

/* ServerSetPreferredSkin_Implementation()
	Set the preferred skin to the skins received from the client call to the server
*/
void ASubjectZero::ServerSetPreferredSkin_Implementation(USkeletalMesh * ThirdPersonSkin, USkeletalMesh * FirstPersonSkin)
{
	SetPreferredSkin(ThirdPersonSkin, FirstPersonSkin);
}

/* ServerSetPreferredSkin_Validate()
	Detect if the skin is even available to the client
*/
bool ASubjectZero::ServerSetPreferredSkin_Validate(USkeletalMesh * ThirdPersonSkin, USkeletalMesh * FirstPersonSkin)
{
	return true;
}

void ASubjectZero::MulticastSetPreferredSkin_Implementation(USkeletalMesh * ThirdPersonSkin, USkeletalMesh * FirstPersonSkin)
{
	SetSkin(ThirdPersonSkin, FirstPersonSkin);
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
AWeapon* ASubjectZero::GetWeapon() const { return Weapon; }
UInventory * ASubjectZero::GetInventory() const { return Inventory; }
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