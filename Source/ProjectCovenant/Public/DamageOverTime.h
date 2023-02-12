// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "DamageOverTime.generated.h"

class ASubjectZero;
class ABaseMode;

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ADamageOverTime : public ATriggerBox
{
	GENERATED_BODY()

	public:
		ADamageOverTime();

		virtual void BeginPlay() override;

		UFUNCTION()
		virtual void Tick(float DeltaTime) override;

		UFUNCTION(BlueprintCallable)
		void IncrementCount();

		UFUNCTION(BlueprintCallable)
		void DecrementCount();

		UPROPERTY()
		TArray<ASubjectZero*> PlayersOverlapping;

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables")
		bool Overlapped = false;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables")
		float DamageAmount = 1.f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables")
		int Count = 0;

		UFUNCTION()
		void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

		UFUNCTION()
		void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

protected:
	UPROPERTY()
	ABaseMode * BaseMode;
};