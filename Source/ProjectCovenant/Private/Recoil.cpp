// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "SubjectZero.h"
#include "Recoil.h"


// Sets default values for this component's properties
URecoil::URecoil()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}


// Called when the game starts
void URecoil::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);
	ReturnDuration = RecoilDuration;
}


// Called every frame
void URecoil::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//TODO: Make the recoil follow a parabolic function that effectively starts at (0,0), reaches a climax at (t/2, RecoilPower), then ends at (t,0)
	// This takes the mathematical form of f(x) = -x^2 + (RecoilPower)x
	// Apply this formula to both the pitch and yaw
	// Plug in the numbers for t and Recoil pattern
	// Adjust the player's controller based on the output
	// Further adjust based on the player's own input (mouse movement) between frames

	RecoilTime += DeltaTime;

	if(Shooter)
	{
		AController * Controller = Shooter->GetController();
		if(Controller)
		{
			FRotator NewRotation = Controller->GetControlRotation();

			// Save the values of where the recoil pattern was calculated at last tick
			float LastPitch = RecoilPitch;
			float LastYaw = RecoilYaw;

			// Calculate where the recoil pattern is at this tick
			RecoilPitch = 20 * (-2 * (RecoilTime * RecoilTime) + RecoilTime);
			RecoilYaw = 0.f;

			// Find the difference between where the recoil was at last tick compared to this tick
			float DeltaPitch = RecoilPitch - LastPitch;
			float DeltaYaw = 0.f;

			Logger::Chat(RecoilTime);

			// Apply the recoil to the rotation
			if(RecoilPitch >= 0.f)
			{
				NewRotation.Pitch = NewRotation.Pitch + DeltaPitch;
				NewRotation.Yaw = NewRotation.Yaw + DeltaYaw;
			}
			else
			{
				NewRotation.Pitch = NewRotation.Pitch - LastPitch;
				NewRotation.Yaw = NewRotation.Yaw - LastYaw;
				SetComponentTickEnabled(false);
			}
			Controller->SetControlRotation(NewRotation);
		}
	}
	else
	{
		Logger::Error("ERROR");
	}
}

void URecoil::Recoil()
{
	if(Shooter->IsLocallyControlled())
	{
		Logger::Chat(Shooter->HasAuthority() ? "Yes" : "No");
		IsRecoilling = true;
		LeftRight = FMath::RandBool() ? -1.f : 1.f;
		RecoilDurationPassed = 0.f;
		ReturnDurationPassed = 0.f;
		PlayerDeltaYaw = 0.f;
		PlayerDeltaPitch = 0.f;
		RecoilTime = 0.f;
		RecoilPitch = 0.f;
		RecoilYaw = 0.f;
		SetComponentTickEnabled(true);
		if(Shooter && Shooter->GetController())
		{
			AController * Controller = Shooter->GetController();
			if(Controller)
			{
				StartingPitch = Controller->GetControlRotation().Pitch;
				StartingYaw = Controller->GetControlRotation().Yaw;
				/*StartPointYaw = Controller->GetControlRotation().Yaw;
				StartPointPitch = Controller->GetControlRotation().Pitch;*/
			}
		}
	}
}

void URecoil::SetShooter(ASubjectZero * NewShooter)
{
	Shooter = NewShooter;
}