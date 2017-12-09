// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectCovenantInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API UProjectCovenantInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UProjectCovenantInstance(const FObjectInitializer & ObjectIn);

private:
	virtual void Init();
	
	void Log(FString msg);
};
