// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ABasePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;
	
	UPROPERTY(Replicated)
	FString Name = "Unknown";

	UPROPERTY(Replicated)
	int Kills = 0;

	UPROPERTY(Replicated)
	int Deaths = 0;

	float LastDamageDealt = 0.f;

	UPROPERTY(Replicated)
	float DamageDealt = 0.f;

	UPROPERTY(Replicated)
	float DamageTaken = 0.f;

	UPROPERTY(Replicated)
	int CurrentPing = 0.f;

public:
	UFUNCTION(Client, Reliable)
	void TookDamage(float Dmg);

	UFUNCTION(Client, Reliable)
	void DealtDamage(float Dmg);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayHitSound(float Dmg);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayGrunt(float Dmg);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FString GetName() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetKills() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetDeaths() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetDamageDealt() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetLastDamageDealt() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetDamageTaken() const;

	void AddKill(int Kill);
	void AddDeath(int Death);
	void AddDamageDealt(float Damage);
	void AddDamageTaken(float Damage);
	void SetName(const FString S);

};
