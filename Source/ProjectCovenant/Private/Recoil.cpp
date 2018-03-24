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
	if(IsRecoilling)
	{
		if(RecoilDurationRemaining - DeltaTime < 0.f)
		{
			DeltaTime = RecoilDurationRemaining;
			IsRecoilling = false;
			DeltaTime = RecoilDurationRemaining * -1.f + DeltaTime;
			SetComponentTickEnabled(false);
		}
		else
		{
			RecoilDurationRemaining -= DeltaTime;
		}

		if(Shooter)
		{
			AController * Controller = Shooter->GetController();
			if(Controller)
			{
				FRotator Rotation = Controller->GetControlRotation();
				Rotation.Pitch += MaxRecoilPitch * DeltaTime;
				Rotation.Yaw += MaxRecoilYaw * DeltaTime;
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
	IsRecoilling = true;
	RecoilDurationRemaining = RecoilDuration;
	SetComponentTickEnabled(true);
}

void URecoil::SetShooter(ASubjectZero * NewShooter)
{
	Shooter = NewShooter;
}