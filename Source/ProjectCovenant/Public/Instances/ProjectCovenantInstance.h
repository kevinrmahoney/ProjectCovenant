// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectCovenantInstance.generated.h"

/**
 * 
 */
UCLASS(Config=TestIni)
class PROJECTCOVENANT_API UProjectCovenantInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	FName ProfileName = "Subject Zero";

	UProjectCovenantInstance(const FObjectInitializer & ObjectIn);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool SetProfileName(FName NewProfileName);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FName GetProfileName();

	UFUNCTION(Exec)
	void Sensitivity(float Sens);

	float GetSensitivity();

private:
	virtual void Init();

	UPROPERTY(Config)
	float cl_sensitivity = 50.f;
};
