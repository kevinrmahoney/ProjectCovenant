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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxRecoilYaw = 3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MinRecoilYaw = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxRecoilPitch = 3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MinRecoilPitch = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float StartPointYaw = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float StartPointPitch = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float EndPointYaw = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float EndPointPitch = 0.f;

	bool IsRecoilling = false;
	float RecoilDuration = 1.f;
	float RecoilDurationRemaining = 1.f;
		
	UPROPERTY()
	ASubjectZero * Shooter;

	UFUNCTION()
	void SetShooter(ASubjectZero * NewShooter);
	
};
