// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BaseMode.generated.h"

class ASubjectZero;
class UItem;
class AWeapon;
class AHumanController;
class AProjectileWeapon;
class ASubjectZerp;
class UPrimitiveComponent;
class APlayerController;

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ABaseMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABaseMode();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASubjectZero> SubjectZeroBP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASpectator> SpectatorBP;

	UPROPERTY()
	TArray<ASubjectZero*> Characters;

	TMap<FString, float> HitBoxDamage;

	virtual void SpawnPlayer(AHumanController * Controller);

	float CalculateLocationalDamage(float BaseDamage, UPrimitiveComponent * HitBox);

	virtual void DealDamage(ASubjectZero * Shooter, ASubjectZero * Victim, float Damage, AWeapon * Weapon, UPrimitiveComponent * HitBox = nullptr);

	virtual void KillPlayer(AHumanController * Controller);

	virtual void BeginPlay();

	virtual void PostLogin(APlayerController * NewPlayer);

	virtual void SpawnInteractable(UItem * Item, FVector Position, FVector Velocity);

	virtual void GiveStartingInventory(ASubjectZero * Character);

	virtual void GiveItemToCharacter(ASubjectZero * Character, UItem * Item);

private:
	TArray<AActor*> SpawnPoints;

	int SpawnCount = 0;
};
