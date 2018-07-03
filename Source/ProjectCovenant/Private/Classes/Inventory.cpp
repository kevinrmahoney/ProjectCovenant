// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "Item.h"
#include "Inventory.h"

UInventory::UInventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Items.SetNumZeroed(19);
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

bool UInventory::CheckItemAt(int Num)
{
	return Num < Items.Num() && Num >= 0.f && Items[Num] != nullptr;
}

bool UInventory::CheckItem(UItem * ItemToCheck)
{
	check(ItemToCheck != nullptr)

	for(UItem * Item : Items)
	{
		if(Item && Item->ItemID == ItemToCheck->ItemID)
		{
			Logger::Log("Item " + Item->ItemID.ToString() + " exists in inventory");
			return true;
		}
	}

	return false;
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
	check(NewItem != nullptr)

	if(!CheckItem(NewItem))
	{
		for(int i = 0; i < Items.Num(); i++)
		{
			if(!Items[i])
			{
				Items[i] = NewItem;
				return;
			}
		}
	}
}

void UInventory::RemoveItem(UItem * OldItem)
{
	check(OldItem != nullptr)

	for(int i = 0; i < Items.Num(); i++)
	{
		if(Items[i] && Items[i]->ItemID == OldItem->ItemID)
		{
			Items[i] = nullptr;
			return;
		}
	}
	Logger::Log("Could not find item to remove");
}

void UInventory::RemoveItemAt(int Index)
{
	if(Index < Items.Num() && Index >= 0)
	{
		Items[Index] = nullptr;
	}
	else
	{
		Logger::Log("Could not find item to remove");
	}
}

TArray<UItem*> UInventory::GetItems()
{
	return Items;
}

void UInventory::SwapItem(int A, int B)
{
	if(A == B || A < 0 || B < 0 || A >= Items.Num() || B >= Items.Num()) return;

	UItem * Temp = Items[A];
	Items[A] = Items[B];
	Items[B] = Temp;
}