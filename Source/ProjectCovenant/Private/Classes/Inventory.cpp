// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Item.h"
#include "Inventory.h"

UInventory::UInventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UInventory::PrintList()
{
	Logger::Log("Array Size : " + FString::FromInt(Items.Num()));
	Logger::Log("Inventory contains: ");
	Logger::Log("=========================");
	for(int i = 0; i < Items.Num(); i++)
	{
		Logger::Log(Items[i]->GetClass()->GetName());
	}
	Logger::Log("=========================");
}

bool UInventory::CheckItem(int Num)
{
	return Num < Items.Num();
}

UItem * UInventory::GetItem(int Num)
{
	if(Items.Num() > Num)
	{
		return Items[Num];
	}
	else
	{
		return nullptr;
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

