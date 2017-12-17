// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Classes/SubjectZero.h"
#include "UnrealNetwork.h"
#include "HitscanWeapon.h"
#include "ProjectCovenantInstance.h"


// Sets default values
ASubjectZero::ASubjectZero(const FObjectInitializer& ObjectInitializer)
{
	// Create a CameraComponent 
	Camera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	Camera->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	// Position the camera a bit above the eyes
	//Camera->RelativeLocation = FVector(0.f, 0, 75.f);
	// Allow the pawn to control rotation.
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
	Logger::Log("Character: Subject Zero");

	// Set initial character movement characteristics
	GetCharacterMovement()->MaxWalkSpeed = MaxGroundSpeed;
	GetCharacterMovement()->AirControl = NormalAirControl;
	GetCharacterMovement()->MaxAcceleration = GroundAcceleration;
	GetCharacterMovement()->GravityScale = 1.f;
	GetCharacterMovement()->JumpZVelocity = JumpSpeed;
	GetCharacterMovement()->GetPhysicsVolume()->TerminalVelocity = 10000.f;

	if(Role == ROLE_AutonomousProxy || Role == ROLE_Authority)
	{
		UGameInstance * Instance = GetGameInstance();

		if(Instance)
		{
			GameInstance = Cast<UProjectCovenantInstance>(Instance);
			if(GameInstance)
			{
				PlayerName = GameInstance->GetProfileName();
				Server_Set_Name(PlayerName);
			}
		}
	}

	// If a simulated proxy, attach the weapon to the character mesh, otherwise attach it to the first person mesh
	Weapon = GetWorld()->SpawnActor<AHitscanWeapon>(WeaponBlueprint);
	if(Role == ROLE_SimulatedProxy)
	{
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("TriggerFinger"));
	}
	else
	{
		Weapon->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("TriggerFinger"));
	}

	Weapon->SetShooter(this);
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

	Move(Movement, Jumping, Sprinting, JetpackActive, IsTriggerPulled, Camera->RelativeRotation.Pitch);

	if(Role == ROLE_SimulatedProxy || HasAuthority())
	{
		DrawDebugString(GetWorld(), FVector(0.f, 0.f, 90.f), PlayerName.ToString(), this, FColor::White, DeltaTime, true);
	}

	Weapon->SetTrigger(IsTriggerPulled);
}

void ASubjectZero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASubjectZero, Health);
	DOREPLIFETIME(ASubjectZero, Armor);
	DOREPLIFETIME(ASubjectZero, Shield);
	DOREPLIFETIME(ASubjectZero, Fuel);
	DOREPLIFETIME(ASubjectZero, Kills);
	DOREPLIFETIME(ASubjectZero, DamageDealt);
	DOREPLIFETIME(ASubjectZero, PlayerName);
}

void ASubjectZero::Move(FVector Client_Movement, bool Client_Jump, bool Client_Sprinting, bool Client_Jetpack, bool Client_Shooting, float Client_Pitch)
{
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

	Server_Move(Client_Movement, Client_Jump, Client_Sprinting, Client_Jetpack, Client_Shooting, Client_Pitch);
}

void ASubjectZero::Server_Move_Implementation(FVector Client_Movement, bool Client_Jump, bool Client_Sprinting, bool Client_Jetpack, bool Client_Shooting, float Client_Pitch)
{
	Movement = Client_Movement;
	Jumping = Client_Jump;
	Sprinting = Client_Sprinting;
	JetpackActive = Client_Jetpack;
	IsTriggerPulled = Client_Shooting;
	Camera->RelativeRotation.Pitch = Client_Pitch;
}

bool ASubjectZero::Server_Move_Validate(FVector Client_Movement, bool Client_Jump, bool Client_Sprinting, bool Client_Jetpack, bool Client_Shooting, float Client_Pitch)
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

void ASubjectZero::Server_Set_Name_Implementation(FName NewName)
{
	PlayerName = NewName;
}

bool ASubjectZero::Server_Set_Name_Validate(FName Name)
{
	return true;
}

bool ASubjectZero::ReceiveDamage(float Dmg)
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
	else
	{
		return false;
	}
	return false;
}

void ASubjectZero::AddDamageDealt(float AddedDamage)
{
	DamageDealt += AddedDamage;
}

void ASubjectZero::AddKill()
{
	Kills += 1;
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
int ASubjectZero::GetKills() const { return Kills; }
int ASubjectZero::GetDamage() const { return DamageDealt; }
FName ASubjectZero::GetPlayerName() const { return PlayerName; }

// Input methods
void ASubjectZero::SetupPlayerInputComponent(class UInputComponent* Input)
{
	// Movement binds
	Input->BindAxis("Yaw", this, &ASubjectZero::InputYaw);
	Input->BindAxis("Pitch", this, &ASubjectZero::InputPitch);
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
	Input->BindAction("Shoot", IE_Released, this, &ASubjectZero::InputShootRelease);
}

void ASubjectZero::InputYaw(float Value) { 
	if(GameInstance != nullptr && GetWorld() != nullptr)
	{
		ASubjectZero::AddControllerYawInput(GetWorld()->GetDeltaSeconds() * GameInstance->GetSensitivity() * Value);
	}
}
void ASubjectZero::InputPitch(float Value) { 
	if(GameInstance != nullptr && GetWorld() != nullptr)
	{
		ASubjectZero::AddControllerPitchInput(GetWorld()->GetDeltaSeconds() * GameInstance->GetSensitivity() * Value);
	}
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
			if(Weapon)
			{
				//Weapon = nullptr;
			}
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
	IsTriggerPulled = true;
}

void ASubjectZero::InputShootRelease()
{
	IsTriggerPulled = false;
}

bool ASubjectZero::Join(FString IPAddress)
{
	if(IPAddress.Equals(""))
	{
		IPAddress = "25.16.209.98";
	}

	Logger::Log("Joining server " + IPAddress);
	UWorld * World = GetWorld();
	if(World)
	{
		APlayerController * PlayerController = World->GetFirstPlayerController();
		if(PlayerController)
		{
			PlayerController->ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);
			return true;
		}
	}
	return false;
}

bool ASubjectZero::Host()
{
	Logger::Log("Hosting server");
	UWorld * World = GetWorld();
	if(World)
	{
		World->ServerTravel("/Game/Maps/TargetRange?listen", true, true);
		return true;
	}
	return false;
}

bool ASubjectZero::Map(FString Map)
{
	Logger::Log("Changing map to " + Map);
	return true;
}