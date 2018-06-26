// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "HumanController.h"
#include "Weapon.h"
#include "ProjectileWeapon.h"
#include "BaseMode.generated.h"

class ASubjectZero;
class UItem;

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ABaseMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASubjectZero> SubjectZeroBlueprint;

	UPROPERTY()
	TArray<ASubjectZero*> Characters;

	UPROPERTY(EditDefaultsOnly)
	UDataTable * ItemDatabase;

	virtual void SpawnPlayer(AHumanController * Controller);

	virtual void DealDamage(ASubjectZero * Shooter, ASubjectZero * Victim, float Damage, AWeapon * Weapon);

	virtual void KillPlayer(AHumanController * Controller);

	virtual void BeginPlay();

	virtual void PostLogin(APlayerController * NewPlayer);

	virtual void GiveStartingInventory(ASubjectZero * Character);

	virtual void GiveItemToCharacter(ASubjectZero * Character, UItem * Item);

	virtual UItem * GetItem(AWeapon * ActorClass);

	virtual TSubclassOf<class AActor> GetActorClass(UItem * Item);

private:
	TArray<AActor*> SpawnPoints;

	int SpawnCount = 0;
};
