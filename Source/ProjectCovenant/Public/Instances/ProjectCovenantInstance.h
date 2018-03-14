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

	UFUNCTION(Exec)
	void Volume(float Volume);

	UFUNCTION(BlueprintImplementableEvent)
	void Event_Volume(float Volume);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool SetSensitivity(float Sens);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetSensitivity();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool SetVolume(float Volume);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetVolume();

	UFUNCTION(Exec, BlueprintPure, BlueprintCallable)
	bool Join(FString IPAddress);

	UFUNCTION(Exec, BlueprintPure, BlueprintCallable)
	bool Host();

	UFUNCTION(Exec, BlueprintPure, BlueprintCallable)
	bool Map(FString Map);

	UFUNCTION(Exec, BlueprintPure, BlueprintCallable)
	bool Kill();

private:
	virtual void Init();

	UPROPERTY(Config)
	float cl_sensitivity = 50.f;

	UPROPERTY(Config)
	float cl_volume = 1.f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MinVolume = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxVolume = 1.f;
};
