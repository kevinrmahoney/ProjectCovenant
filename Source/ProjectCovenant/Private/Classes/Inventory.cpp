// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Item.h"
#include "Inventory.h"

UInventory::UInventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UInventory::PrintList()
{
	// check if Items has elements
	if(&Items != nullptr)
	{
		Logger::Log("Inventory contains: ");
		Logger::Log("=========================");
		for(int i = 0; i < Items.Num(); i++)
		{
			if(Items[i])
			{
				Logger::Log(Items[i]->GetClass()->GetName());
			}
		}
		Logger::Log("=========================");
	}
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
	PrintList();
}

void UInventory::AddItem(UItem * NewItem)
{
	for(UItem * Item : Items)
	{
		if(Item->ItemID == NewItem->ItemID)
		{
			Logger::Log("Item " + Item->ItemID.ToString() + " exists in inventory, cannot have multiple of the same item");
			return;
		}
	}
	Items.Add(NewItem);
}

void UInventory::RemoveItem(UItem * OldItem)
{
	for(UItem * Item : Items)
	{
		if(Item->ItemID == OldItem->ItemID)
		{
			Items.Remove(Item);
			return;
		}
	}
	Logger::Log("Could not find item to remove");
}

TArray<UItem*> UInventory::GetItems()
{
	return Items;
}