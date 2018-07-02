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
	ABaseMode();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASubjectZero> SubjectZeroBlueprint;

	UPROPERTY()
	TArray<ASubjectZero*> Characters;

	UPROPERTY(EditDefaultsOnly)
	UDataTable * ItemDatabase;

	TMap<FString, float> HitBoxDamage;

	virtual void SpawnPlayer(AHumanController * Controller);

	float CalculateLocationalDamage(float BaseDamage, UPrimitiveComponent * HitBox);

	virtual void DealDamage(ASubjectZero * Shooter, ASubjectZero * Victim, float Damage, AWeapon * Weapon, UPrimitiveComponent * HitBox = nullptr);

	virtual void KillPlayer(AHumanController * Controller);

	virtual void BeginPlay();

	virtual void PostLogin(APlayerController * NewPlayer);

	virtual void DropItem(UItem * Item, FVector Position, FVector Velocity);

	virtual void GiveStartingInventory(ASubjectZero * Character);

	virtual void GiveItemToCharacter(ASubjectZero * Character, UItem * Item);

	virtual UItem * GetItem(UStaticMesh * StaticMesh);

	virtual UItem * GetItem(AWeapon * ActorClass);

	virtual TSubclassOf<class AActor> GetActorClass(UItem * Item);

private:
	TArray<AActor*> SpawnPoints;

	int SpawnCount = 0;
};
