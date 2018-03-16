// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Item.h"


UItem::UItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

FString UItem::ToString()
{
	return "Item";
}