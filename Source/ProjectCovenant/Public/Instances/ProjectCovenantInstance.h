// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectCovenantInstance.generated.h"

/**
 * 
 */
UCLASS(Config=Settings)
class PROJECTCOVENANT_API UProjectCovenantInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config)
	FName ProfileName;

	UProjectCovenantInstance(const FObjectInitializer & ObjectIn);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool SetProfileName(FName NewProfileName);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FName GetProfileName();

	UFUNCTION(Exec)
	void Sensitivity(float Sens);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool SetSensitivity(float Sens);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetSensitivity();

	UFUNCTION(Exec, BlueprintPure, BlueprintCallable)
	bool Join(FString IPAddress);

	UFUNCTION(Exec, BlueprintPure, BlueprintCallable)
	bool Host();

	UFUNCTION(Exec, BlueprintPure, BlueprintCallable)
	bool Map(FString Map);

private:
	virtual void Init();

	UPROPERTY(Config)
	float cl_sensitivity = 50.f;
};
