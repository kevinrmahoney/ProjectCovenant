// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BaseState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOVENANT_API ABaseState : public AGameState
{
	GENERATED_BODY()

public:
	ABaseState();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	UPROPERTY(Replicated)
	float TimeLeft = 3600.f;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetTimeLeft();

	UFUNCTION(NetMulticast, Reliable)
	void GameOver();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOverScreen();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UDataTable * ItemDatabase;

	UFUNCTION(BlueprintCallable)
	UItem * GetItemFromStaticMesh(UStaticMesh * StaticMesh);

	UFUNCTION(BlueprintCallable)
	UItem * GetItemFromActorClass(AActor * ActorClass);

	UFUNCTION(BlueprintCallable)
	TSubclassOf<class AActor> GetActorClassFromItem(UItem * Item);

	UFUNCTION(BlueprintCallable)
	UStaticMesh * GetMeshFromItem(UItem * Item);

	UFUNCTION(BlueprintCallable)
	UTexture2D * GetThumbnailFromItem(UItem * Item);
};
