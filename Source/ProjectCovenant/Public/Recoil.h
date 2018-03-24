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
	float MaxRecoilYaw = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinRecoilYaw = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxRecoilPitch = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinRecoilPitch = 0.f;

	float StartPointYaw = 0.f;
	float StartPointPitch = 0.f;
	float EndPointYaw = 0.f;
	float EndPointPitch = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RecoilDuration = 0.2f;

	bool IsRecoilling = false;
	float RecoilDurationRemaining = 0.f;
		
	UPROPERTY()
	ASubjectZero * Shooter;

	UFUNCTION()
	void SetShooter(ASubjectZero * NewShooter);
	
};
