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
	void Recoil(float Multiplier = 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RecoilPitchMagnitudeMax = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RecoilPitchMagnitudeMin = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RecoilYawMagnitudeMax = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RecoilYawMagnitudeMin = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RecoilDuration = 1.f;

	float LeftRight = 1.f;
	float RecoilPitchMagnitude = 0.f;
	float RecoilYawMagnitude = 0.f;

	float RecoilTime = 0.f;
	float RecoilPitch = 0.f;
	float RecoilYaw = 0.f;
		
	UPROPERTY()
	ASubjectZero * Shooter;

	UFUNCTION()
	void SetShooter(ASubjectZero * NewShooter);
	
};
