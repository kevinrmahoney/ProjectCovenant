// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
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

		if(IsLocallyControlled())
		{
			Velocity = Velocity + Acceleration * Movement;
			//Velocity.Z = FMath::Max(Velocity.Z - Acceleration * 0.5f, TerminalVelocity);
			AddActorLocalOffset(Velocity * DeltaTime);
		}
		ApplyAirResistance();
	}
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

void ADropPod::Interact(ASubjectZero * Interactor)
{
	if(!Occupant && Interactor)
	{
		Occupant = Interactor;
		Enter();
	}
}

void ADropPod::Enter()
{
	if(HasAuthority() && Occupant->GetController())
	{
		Occupant->SetIsInPod(true);
		Occupant->AttachToComponent(DropPodMesh, FAttachmentTransformRules::KeepRelativeTransform);
		Occupant->SetActorLocation(OccupantSocket->GetComponentLocation());

		Logger::Chat("Controller " + Occupant->GetController()->GetName() + " possessing Drop Pod");
		Occupant->GetController()->Possess(this);
	}
	else
	{
		Logger::Chat("Could not get controller");
	}
}

void ADropPod::Leave()
{
	if(GetController() && Occupant)
	{
		Occupant->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Occupant->SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, 2000.f));
		Occupant->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Occupant->GetCapsuleComponent()->SetEnableGravity(true);
		Occupant->GetCharacterMovement()->Velocity = GetVelocity() + FVector(0.f, 0.f, 1000.f);
		Occupant->GetCharacterMovement()->GravityScale = 1.f;
		Occupant->GetMesh()->SetEnableGravity(true);
		GetController()->Possess(Occupant);
		Occupant->SetIsInPod(false);
		Occupant = nullptr;
	}
}

void ADropPod::ApplyAirResistance()
{
	if(IsLocallyControlled() || HasAuthority())
	{
		//float Magnitude = GetMovementComponent()->Velocity.Size();
		//FVector Direction = GetMovementComponent()->Velocity.GetSafeNormal();
		//FVector Force = -1.f * Direction * (Magnitude * Magnitude) * AirResistanceConstant * (GetWorld()->DeltaTimeSeconds);
		//GetMovementComponent()->Velocity += Force;
		Velocity = FVector(100.f, 0.f, 0.f);
	}
}

void ADropPod::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	HasLanded = true;
	Logger::Chat("HIT");
	Velocity = FVector::ZeroVector;
	Movement = FVector::ZeroVector;
	SetActorTickEnabled(false);
}

void ADropPod::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HasLanded = true;
	bUseControllerRotationYaw = false;
	Logger::Chat("OVERLAP");
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
	Logger::Chat("InputForwardPress");
	Movement.X = FMath::Clamp(Movement.X + 1.f, -1.f, 1.f);
}
void ADropPod::InputForwardRelease()
{
	Logger::Chat("InputForwardRelease");
	Movement.X = FMath::Clamp(Movement.X - 1.f, -1.f, 1.f);
}
void ADropPod::InputBackwardPress()
{
	Movement.X = FMath::Clamp(Movement.X - 1.f, -1.f, 1.f);
	Logger::Chat("InputBackwardPress");
}
void ADropPod::InputBackwardRelease()
{
	Movement.X = FMath::Clamp(Movement.X + 1.f, -1.f, 1.f);
	Logger::Chat("InputBackwardRelease");
}
void ADropPod::InputLeftPress()
{
	Movement.Y = FMath::Clamp(Movement.Y - 1.f, -1.f, 1.f);
	Logger::Chat("InputLeftPress");
}
void ADropPod::InputLeftRelease()
{
	Movement.Y = FMath::Clamp(Movement.Y + 1.f, -1.f, 1.f);
	Logger::Chat("InputLeftRelease");
}
void ADropPod::InputRightPress()
{
	Movement.Y = FMath::Clamp(Movement.Y + 1.f, -1.f, 1.f);
	Logger::Chat("InputRightPress");
}
void ADropPod::InputRightRelease()
{
	Movement.Y = FMath::Clamp(Movement.Y - 1.f, -1.f, 1.f);
	Logger::Chat("InputRightRelease");
}
void ADropPod::InputJumpPress()
{
	Movement.Z = 1.f;
	Logger::Chat("InputJumpPress");
}
void ADropPod::InputJumpRelease()
{
	Movement.Z = 0.f;
	Logger::Chat("InputJumpRelease");
}

void ADropPod::InputCrouchPress()
{
	Logger::Chat("InputCrouchPress");
}
void ADropPod::InputCrouchRelease()
{
	Logger::Chat("InputCrouchRelease");
}

void ADropPod::InputInteractPress()
{
	Logger::Chat("InputInteractPress");
	Leave();
}