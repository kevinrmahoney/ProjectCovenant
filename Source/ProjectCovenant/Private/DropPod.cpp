// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "UnrealNetwork.h"
#include "DropPod.h"
#include "SubjectZero.h"
#include "ProjectCovenantInstance.h"
#include "HumanController.h"


// Sets default values
ADropPod::ADropPod()
{
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	SetRootComponent(InteractionBox);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->AttachToComponent(InteractionBox, FAttachmentTransformRules::KeepRelativeTransform);

	// Mesh
	DropPodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropPod"));
	DropPodMesh->AttachToComponent(CollisionBox, FAttachmentTransformRules::KeepRelativeTransform);

	// Mesh
	DropPodDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropPodDoor"));
	DropPodDoorMesh->AttachToComponent(DropPodMesh, FAttachmentTransformRules::KeepRelativeTransform);

	// Create a CameraComponent 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	Camera->AttachToComponent(DropPodMesh, FAttachmentTransformRules::KeepRelativeTransform);

	OccupantSocket = CreateDefaultSubobject<USceneComponent>(TEXT("OccupantSocket"));
	OccupantSocket->AttachToComponent(DropPodMesh, FAttachmentTransformRules::KeepRelativeTransform);

	// Allow the pawn to control rotation
	Camera->bUsePawnControlRotation = true;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);
}

// Called when the game starts or when spawned
void ADropPod::BeginPlay()
{
	Super::BeginPlay();
	if(HasAuthority())
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADropPod::OnBeginOverlap);
		CollisionBox->OnComponentHit.AddDynamic(this, &ADropPod::OnHit);
	}
}

void ADropPod::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	// The follow variables are replicated from server to the clients
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADropPod, ReplicatedLocation)
	DOREPLIFETIME(ADropPod, Velocity)
	DOREPLIFETIME(ADropPod, HasLanded)
	DOREPLIFETIME_CONDITION(ADropPod, ReplicatedRotation, COND_SimulatedOnly)
}

// Called to bind functionality to input
void ADropPod::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	AHumanController * Human = Cast<AHumanController>(GetController());
	if(Human && PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("Yaw", this, &ADropPod::InputYaw);
		PlayerInputComponent->BindAxis("Pitch", this, &ADropPod::InputPitch);
		PlayerInputComponent->BindAction("Forward", IE_Pressed, this, &ADropPod::InputForwardPress);
		PlayerInputComponent->BindAction("Forward", IE_Released, this, &ADropPod::InputForwardRelease);
		PlayerInputComponent->BindAction("Backward", IE_Pressed, this, &ADropPod::InputBackwardPress);
		PlayerInputComponent->BindAction("Backward", IE_Released, this, &ADropPod::InputBackwardRelease);
		PlayerInputComponent->BindAction("Left", IE_Pressed, this, &ADropPod::InputLeftPress);
		PlayerInputComponent->BindAction("Left", IE_Released, this, &ADropPod::InputLeftRelease);
		PlayerInputComponent->BindAction("Right", IE_Pressed, this, &ADropPod::InputRightPress);
		PlayerInputComponent->BindAction("Right", IE_Released, this, &ADropPod::InputRightRelease);
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADropPod::InputJumpPress);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ADropPod::InputJumpRelease);
		PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ADropPod::InputCrouchPress);
		PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ADropPod::InputCrouchRelease);
		PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ADropPod::InputInteractPress);
		GetController()->InputComponent = PlayerInputComponent;
	}
}

// Called every frame
void ADropPod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!HasLanded)
	{
		if(Occupant)
		{
			Occupant->SetActorLocation(OccupantSocket->GetComponentLocation());
			Occupant->SetActorRotation(GetActorForwardVector().Rotation());
		}

		Move(DeltaTime);

		if(Role == ROLE_AutonomousProxy)
		{
			ServerSetMovement(Movement);
			ServerSetRotation(GetActorRotation());
		}

		if(HasAuthority())
		{
			ReplicatedLocation = GetActorLocation();
			ReplicatedRotation = GetActorRotation();
		}
	}
}

void ADropPod::Move(float Time)
{
	if(Controller)
	{
		FVector RotatedMovement = Movement;
		FRotator Rotation = GetActorRotation();
		Rotation.Pitch = 0;

		Velocity = Velocity + Acceleration * Rotation.RotateVector(RotatedMovement);
		float VelocityZ = Velocity.Z;
		if(Velocity.Size2D() > MaxSpeed)
		{
			Velocity = Velocity.GetSafeNormal2D() * MaxSpeed;
		}

		//Velocity.Z = FMath::Max(VelocityZ - DropAcceleration, TerminalVelocity);
		AddActorWorldOffset(Velocity * Time);
	}
}

void ADropPod::ServerSetMovement_Implementation(FVector NewMovement)
{
	Movement = NewMovement;
}

bool ADropPod::ServerSetMovement_Validate(FVector NewMovement)
{
	return true;
}

void ADropPod::ServerSetRotation_Implementation(FRotator NewRotation)
{
	SetActorRotation(NewRotation);
}

bool ADropPod::ServerSetRotation_Validate(FRotator NewRotation)
{
	return true;
}

void ADropPod::UpdateLocation()
{
	SetActorLocation(ReplicatedLocation);
}

void ADropPod::UpdateRotation()
{
	SetActorRotation(ReplicatedRotation);
}

void ADropPod::Interact(ASubjectZero * Interactor)
{
	if(HasAuthority())
	{
		Enter(Interactor);
	}
}

void ADropPod::SetOccupant(ASubjectZero * NewOccupant)
{
	Logger::Chat(NewOccupant ? "Enter" : "Leave");

	// Save the old occupant
	ASubjectZero * OldOccupant = Occupant;

	// If the NewOccupant, put his character in the pod
	if(NewOccupant)
	{
		NewOccupant->SetIsInPod(true);
		NewOccupant->AttachToComponent(DropPodMesh, FAttachmentTransformRules::KeepRelativeTransform);
		NewOccupant->SetActorLocation(OccupantSocket->GetComponentLocation());
		NewOccupant->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		NewOccupant->GetCapsuleComponent()->SetEnableGravity(false);
		NewOccupant->GetMesh()->SetEnableGravity(false);
	}
	
	// If there used to be an occupant, take the character out of the pod
	if(OldOccupant)
	{
		OldOccupant->SetIsInPod(false);
		OldOccupant->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		OldOccupant->SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, 500.f));
		OldOccupant->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		OldOccupant->GetCapsuleComponent()->SetEnableGravity(true);
		OldOccupant->GetCharacterMovement()->Velocity = GetVelocity() + FVector(0.f, 0.f, 100.f);
		OldOccupant->GetCharacterMovement()->GravityScale = 1.f;
		OldOccupant->GetMesh()->SetEnableGravity(true);
	}

	Occupant = NewOccupant;
}

/* Enter()
	Function handling a request by a character to enter this drop pod
	If called on a client, call on the server function. If called on the server, call on the multicast function
*/
void ADropPod::Enter(ASubjectZero * NewOccupant)
{
	if(HasAuthority())
	{
		MulticastEnter(NewOccupant);
	}
	else
	{
		ServerEnter(NewOccupant);
	}
}

/* ServerEnter()
	Server function handling a request by a character to enter this drop pod
*/
void ADropPod::ServerEnter_Implementation(ASubjectZero * NewOccupant)
{
	Enter(NewOccupant);
}

bool ADropPod::ServerEnter_Validate(ASubjectZero * NewOccupant)
{
	return true;
}

/* MulticastEnter()
	Multicast function handling a request by a character to enter this drop pod.
*/
void ADropPod::MulticastEnter_Implementation(ASubjectZero * NewOccupant)
{
	if(HasAuthority() && NewOccupant && NewOccupant->GetController())
	{
		if(AHumanController * Human = Cast<AHumanController>(NewOccupant->GetController()))
		{
			Human->Possess(this);
		}
	}
	SetOccupant(NewOccupant);
}

void ADropPod::Leave()
{
	if(HasAuthority())
	{
		MulticastLeave();
	}
	else
	{
		ServerLeave();
	}
}

void ADropPod::ServerLeave_Implementation()
{
	Leave();
}

bool ADropPod::ServerLeave_Validate()
{
	return true;
}

void ADropPod::MulticastLeave_Implementation()
{
	if(HasAuthority() && GetController())
	{
		if(AHumanController * Human = Cast<AHumanController>(GetController()))
		{
			Human->Possess(Occupant);
		}
	}
	SetOccupant(nullptr);
}

void ADropPod::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	HasLanded = true;
	bUseControllerRotationYaw = false;
	Velocity = FVector::ZeroVector;
	Movement = FVector::ZeroVector;
	SetActorTickEnabled(false);
}

void ADropPod::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HasLanded = true;
	bUseControllerRotationYaw = false;
	Velocity = FVector::ZeroVector;
	Movement = FVector::ZeroVector;
	SetActorTickEnabled(false);
}

void ADropPod::InputYaw(float Value)
{
	UProjectCovenantInstance * GameInstance = Cast<UProjectCovenantInstance>(GetGameInstance());
	if(GameInstance)
	{
		AddControllerYawInput(GetWorld()->GetDeltaSeconds() * Value * GameInstance->GetSensitivity());
	}
}
void ADropPod::InputPitch(float Value)
{
	UProjectCovenantInstance * GameInstance = Cast<UProjectCovenantInstance>(GetGameInstance());
	if(GameInstance)
	{
		AddControllerPitchInput(GetWorld()->GetDeltaSeconds() * Value * GameInstance->GetSensitivity());
	}
}
void ADropPod::InputForwardPress()
{
	Movement.X = FMath::Clamp(Movement.X + 1.f, -1.f, 1.f);
}
void ADropPod::InputForwardRelease()
{
	Movement.X = FMath::Clamp(Movement.X - 1.f, -1.f, 1.f);
}
void ADropPod::InputBackwardPress()
{
	Movement.X = FMath::Clamp(Movement.X - 1.f, -1.f, 1.f);
}
void ADropPod::InputBackwardRelease()
{
	Movement.X = FMath::Clamp(Movement.X + 1.f, -1.f, 1.f);
}
void ADropPod::InputLeftPress()
{
	Movement.Y = FMath::Clamp(Movement.Y - 1.f, -1.f, 1.f);
}
void ADropPod::InputLeftRelease()
{
	Movement.Y = FMath::Clamp(Movement.Y + 1.f, -1.f, 1.f);
}
void ADropPod::InputRightPress()
{
	Movement.Y = FMath::Clamp(Movement.Y + 1.f, -1.f, 1.f);
}
void ADropPod::InputRightRelease()
{
	Movement.Y = FMath::Clamp(Movement.Y - 1.f, -1.f, 1.f);
}
void ADropPod::InputJumpPress()
{
	Movement.Z = 1.f;
}
void ADropPod::InputJumpRelease()
{
	Movement.Z = 0.f;
}

void ADropPod::InputCrouchPress()
{
}
void ADropPod::InputCrouchRelease()
{
}

void ADropPod::InputInteractPress()
{
	Leave();
}