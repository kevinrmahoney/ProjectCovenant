// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Recoil.generated.h"

class ASubjectZero;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCOVENANT_API URecoil : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecoil();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void Recoil();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxInitialRecoilSpeedYaw = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinInitialRecoilSpeedYaw = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxInitialRecoilSpeedPitch = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinInitialRecoilSpeedPitch = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RecoilDuration = 0.2f;

	float ReturnDuration = 0.f;
	float ReturnDurationPassed = 0.f;

	float LeftRight = 1.f;

	float RecoilTime = 0.f;
	float RecoilPitch = 0.f;
	float RecoilYaw = 0.f;

	float StartingYaw = 0.f;
	float StartingPitch = 0.f;

	float PlayerDeltaYaw = 0.f;
	float PlayerDeltaPitch = 0.f;

	bool IsRecoilling = false;
	bool IsReturning = false;
	float RecoilDurationPassed = 0.f;
		
	UPROPERTY()
	ASubjectZero * Shooter;

	UFUNCTION()
	void SetShooter(ASubjectZero * NewShooter);
	
};
