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
	if(IsRecoilling)
	{
		if(RecoilDurationPassed + DeltaTime > RecoilDuration)
		{
			RecoilDurationPassed = RecoilDuration;
			IsRecoilling = false;
			IsReturning = true;
			DeltaTime = RecoilDuration - RecoilDurationPassed;
		}
		else
		{
			RecoilDurationPassed += DeltaTime;
		}

		if(Shooter)
		{
			AController * Controller = Shooter->GetController();
			if(Controller)
			{
				float AddedPitch = MaxInitialRecoilSpeedPitch * (1 - (RecoilDurationPassed / RecoilDuration)) * (1 - (RecoilDurationPassed / RecoilDuration)) * DeltaTime;
				float AddedYaw = LeftRight * MaxInitialRecoilSpeedYaw * (1 - (RecoilDurationPassed / RecoilDuration)) * (1 - (RecoilDurationPassed / RecoilDuration)) * DeltaTime;
				FRotator Rotation = Controller->GetControlRotation();
				Rotation.Pitch += AddedPitch;
				Rotation.Yaw += AddedYaw;
				DeltaPitch += AddedPitch;
				DeltaYaw += AddedYaw;
				Controller->SetControlRotation(Rotation);
			}
		}
		else
		{
			Logger::Error("Recoil component " + GetName() + " has no weapon");
		}
	}
	else if(IsReturning)
	{
		if(ReturnDurationPassed + DeltaTime > ReturnDuration)
		{
			ReturnDurationPassed = ReturnDuration;
			IsReturning = false;
			SetComponentTickEnabled(false);
			DeltaTime = ReturnDuration - ReturnDurationPassed;
		}
		else
		{
			ReturnDurationPassed += DeltaTime;
		}

		if(Shooter)
		{
			AController * Controller = Shooter->GetController();
			if(Controller)
			{
				FRotator Rotation = Controller->GetControlRotation();
				Rotation.Pitch -= (DeltaPitch / ReturnDuration) * DeltaTime;
				if(LeftRight == -1.f)
				{
					Rotation.Yaw -= (DeltaYaw / ReturnDuration) * DeltaTime;
				}
				else
				{
					Rotation.Yaw -= LeftRight * (DeltaYaw / ReturnDuration) * DeltaTime;
				}
				Controller->SetControlRotation(Rotation);
			}
		}
		else
		{
			Logger::Error("Recoil component " + GetName() + " has no weapon");
		}
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
		DeltaYaw = 0.f;
		DeltaPitch = 0.f;
		SetComponentTickEnabled(true);
		if(Shooter && Shooter->GetController())
		{
			AController * Controller = Shooter->GetController();
			if(Controller)
			{
				StartPointYaw = Controller->GetControlRotation().Yaw;
				StartPointPitch = Controller->GetControlRotation().Pitch;
			}
		}
	}
}

void URecoil::SetShooter(ASubjectZero * NewShooter)
{
	Shooter = NewShooter;
}