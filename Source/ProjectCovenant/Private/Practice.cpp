// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Practice.h"
#include "SubjectZero.h"

APractice::APractice(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DefaultPawnClass = ASubjectZero::StaticClass();
}

void APractice::StartPlay() 
{
	Super::StartPlay();

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Mode: Practice"));
	}

}