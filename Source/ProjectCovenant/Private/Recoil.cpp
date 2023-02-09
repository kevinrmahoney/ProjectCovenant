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
}


// Called every frame
void URecoil::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
			RecoilPitch = RecoilPitchMagnitude * (-(1.f/ RecoilDuration) * (RecoilTime * RecoilTime) + RecoilTime);
			RecoilYaw = RecoilYawMagnitude * (-(1.f / RecoilDuration) * (RecoilTime * RecoilTime) + RecoilTime);

			// Find the difference between where the recoil was at last tick compared to this tick
			float DeltaPitch = RecoilPitch - LastPitch;
			float DeltaYaw = RecoilYaw - LastYaw;

			// Apply the recoil to the rotation
			if(RecoilPitch >= 0.f)
			{
				NewRotation.Pitch = NewRotation.Pitch + DeltaPitch;
				NewRotation.Yaw = NewRotation.Yaw + DeltaYaw;
			}
			// Apply only a portion of the recoil (otherwise, recoil would go under the original firing point)
			else
			{
				NewRotation.Pitch = NewRotation.Pitch - LastPitch;
				NewRotation.Yaw = NewRotation.Yaw - LastYaw;

				SetComponentTickEnabled(false);
			}
			Controller->SetControlRotation(NewRotation);
		}
	}
}

void URecoil::Recoil(float Multiplier)
{
	if(Shooter && Shooter->IsLocallyControlled())
	{
		SetComponentTickEnabled(false);

		// Decide whether the yaw recoil is to the left (-1) or the right (1)
		LeftRight = FMath::RandBool() ? -1.f : 1.f;

		// Reset time, pitch and yaw trackers
		RecoilTime = 0.f;
		RecoilPitch = 0.f;
		RecoilYaw = 0.f;

		// Determine the random yaw and pitch factors
		RecoilPitchMagnitude = FMath::RandRange(RecoilPitchMagnitudeMin, RecoilPitchMagnitudeMax) * Multiplier;
		RecoilYawMagnitude = FMath::RandRange(RecoilYawMagnitudeMin, RecoilYawMagnitudeMax) * LeftRight * Multiplier;

		
		// Disabling recoil for now SetComponentTickEnabled(true);
	}
}

void URecoil::SetShooter(ASubjectZero * NewShooter)
{
	Shooter = NewShooter;
}