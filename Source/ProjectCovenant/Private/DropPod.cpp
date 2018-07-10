// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "DropPod.h"
#include "SubjectZero.h"
#include "ProjectCovenantInstance.h"
#include "HumanController.h"


// Sets default values
ADropPod::ADropPod()
{
	// Mesh
	DropPodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropPod"));
	SetRootComponent(DropPodMesh);

	// Mesh
	DropPodDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropPodDoor"));
	DropPodDoorMesh->AttachToComponent(DropPodMesh, FAttachmentTransformRules::KeepRelativeTransform);

	// Create a CameraComponent 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	Camera->AttachToComponent(DropPodMesh, FAttachmentTransformRules::KeepRelativeTransform);

	// Position the camera a bit above the eyes
	Camera->RelativeLocation = FVector(0.f, 0, 250.f);
	// Allow the pawn to control rotation
	Camera->bUsePawnControlRotation = true;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADropPod::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADropPod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADropPod::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	
	if(AHumanController * Human = Cast<AHumanController>(GetController()))
	{
		Human->InputComponent->ClearActionBindings();
		Human->InputComponent->AxisBindings.Empty();
	}

	if(InputComponent)
	{
		InputComponent->ClearActionBindings();
		InputComponent->BindAxis("Yaw", this, &ADropPod::InputYaw);
		InputComponent->BindAxis("Pitch", this, &ADropPod::InputPitch);
		InputComponent->BindAction("Forward", IE_Pressed, this, &ADropPod::InputForwardPress);
		InputComponent->BindAction("Forward", IE_Released, this, &ADropPod::InputForwardRelease);
		InputComponent->BindAction("Backward", IE_Pressed, this, &ADropPod::InputBackwardPress);
		InputComponent->BindAction("Backward", IE_Released, this, &ADropPod::InputBackwardRelease);
		InputComponent->BindAction("Left", IE_Pressed, this, &ADropPod::InputLeftPress);
		InputComponent->BindAction("Left", IE_Released, this, &ADropPod::InputLeftRelease);
		InputComponent->BindAction("Right", IE_Pressed, this, &ADropPod::InputRightPress);
		InputComponent->BindAction("Right", IE_Released, this, &ADropPod::InputRightRelease);
		InputComponent->BindAction("Jump", IE_Pressed, this, &ADropPod::InputJumpPress);
		InputComponent->BindAction("Jump", IE_Released, this, &ADropPod::InputJumpRelease);
		InputComponent->BindAction("Crouch", IE_Pressed, this, &ADropPod::InputCrouchPress);
		InputComponent->BindAction("Crouch", IE_Released, this, &ADropPod::InputCrouchRelease);
		InputComponent->BindAction("Use", IE_Pressed, this, &ADropPod::InputInteractPress);
	}
}

void ADropPod::Interact(ASubjectZero * Interactor)
{
	Logger::Chat(Interactor->GetName());

	if(Interactor->GetController())
	{
		Interactor->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Interactor->GetCapsuleComponent()->SetEnableGravity(false);
		Interactor->AttachToComponent(DropPodMesh, FAttachmentTransformRules::KeepRelativeTransform);
		Interactor->SetActorLocation(GetActorLocation());
		Interactor->SetActorRotation(GetActorRotation());
		Interactor->GetCharacterMovement()->Velocity = FVector::ZeroVector;
		Interactor->GetCharacterMovement()->GravityScale = 0.f;
		Interactor->GetMesh()->SetEnableGravity(false);

		Logger::Chat("Controller " + Interactor->GetController()->GetName() + " possessing Drop Pod");
		Interactor->GetController()->Possess(this);
	}
	else
	{
		Logger::Chat("Could not get controller");
	}
}

void ADropPod::InputYaw(float Value)
{
	Logger::Chat("InputYaw");
	UProjectCovenantInstance * GameInstance = Cast<UProjectCovenantInstance>(GetGameInstance());
	if(GameInstance)
	{
		FRotator Rotation = GetControlRotation();
		AddControllerYawInput(GetWorld()->GetDeltaSeconds() * Value * GameInstance->GetSensitivity());
		Rotation.Yaw = GetControlRotation().Yaw + 180.f;
		Rotation.Pitch = 0.f;
		SetActorRotation(Rotation);
	}
}
void ADropPod::InputPitch(float Value)
{
	Logger::Chat("InputPitch");
	UProjectCovenantInstance * GameInstance = Cast<UProjectCovenantInstance>(GetGameInstance());
	if(GameInstance)
	{
		AddControllerPitchInput(GetWorld()->GetDeltaSeconds() * Value * GameInstance->GetSensitivity());
	}
}
void ADropPod::InputForwardPress()
{
	Logger::Chat("InputForwardPress");
}
void ADropPod::InputForwardRelease()
{
	Logger::Chat("InputForwardRelease");
}
void ADropPod::InputBackwardPress()
{
	Logger::Chat("InputBackwardPress");
}
void ADropPod::InputBackwardRelease()
{
	Logger::Chat("InputBackwardRelease");
}
void ADropPod::InputLeftPress()
{
	Logger::Chat("InputLeftPress");
}
void ADropPod::InputLeftRelease()
{
	Logger::Chat("InputLeftRelease");
}
void ADropPod::InputRightPress()
{
	Logger::Chat("InputRightPress");
}
void ADropPod::InputRightRelease()
{
	Logger::Chat("InputRightRelease");
}
void ADropPod::InputJumpPress()
{
	Logger::Chat("InputJumpPress");
}
void ADropPod::InputJumpRelease()
{
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
}