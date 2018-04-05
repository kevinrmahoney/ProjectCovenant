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

void UItem::SetLastShotTimeStamp(UWorld * World)
{
	Logger::Log("Setting last shot time stamp...");
	if(World)
	{
		float Timestamp = World->GetRealTimeSeconds();
		LastShotTimeStamp = Timestamp;
		Logger::Log("Set last shot time stamp to: " + FString::SanitizeFloat(LastShotTimeStamp));
	}
	else
	{
		Logger::Log("GetWorld returned null");
	}
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