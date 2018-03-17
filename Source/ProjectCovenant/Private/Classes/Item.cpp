// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Item.h"


UItem::UItem()
{
}

TSubclassOf<class AActor> UItem::GetActorClass()
{
	return ItemBlueprint;
}

FString UItem::ToString()
{
	return "Item";
}