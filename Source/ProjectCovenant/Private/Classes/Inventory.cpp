// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Item.h"
#include "Inventory.h"

UInventory::UInventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UInventory::PrintList()
{
	for(int i = 0; i < Items.Num(); i++)
	{
		Logger::Chat(Items[i]->ToString());
	}
}

void UInventory::AddItem(UItem * NewItem)
{
	Items.Add(NewItem);
}

void UInventory::RemoveItem(UItem * Item)
{
	Items.Remove(Item);
}