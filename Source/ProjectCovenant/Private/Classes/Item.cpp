// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Item.h"


UItem::UItem()
{
}

FString UItem::ToString()
{
	return "Item";
}

int UItem::GetItemID()
{
	return ItemID;
}