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

FName UItem::GetItemID()
{
	return ItemID;
}

UItem * UItem::UnserializeItem(FItemSerialized Item)
{
	UItem * UnserializedItem = NewObject<UItem>();
	if(UnserializedItem)
	{
		UnserializedItem->Count = Item.Count;
		UnserializedItem->Equipped = false;
		UnserializedItem->ItemID = Item.ItemID;
	}
	return UnserializedItem;
}

FItemSerialized UItem::SerializeItem(UItem * Item)
{
	FItemSerialized SerializedItem = FItemSerialized();
	SerializedItem.Count = Item->Count;
	SerializedItem.ItemID = Item->ItemID;
	return SerializedItem;
}