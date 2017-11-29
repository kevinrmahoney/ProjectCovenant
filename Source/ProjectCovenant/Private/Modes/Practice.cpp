// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Practice.h"
#include "SubjectZero.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

APractice::APractice(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DefaultPawnClass = ASubjectZero::StaticClass();

	// Wizardry involving turning Blueprints into objects. 
	// PlayerHUD is a blueprint that creates widgets (ex. BP_HUD). Make this
	static ConstructorHelpers::FClassFinder <AHUD> PlayerHUD(TEXT("/Game/Blueprints/HUD/PlayerHUD_BP"));
	HUDClass = (UClass*)PlayerHUD.Class;
}

void APractice::StartPlay() 
{
	Super::StartPlay();

	ASubjectZero* Character = Cast<ASubjectZero>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (PlayerHUDClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Mode: Practice"));
	}

}