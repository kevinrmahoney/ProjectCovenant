// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "UnrealNetwork.h"
#include "BaseState.h"
#include "Item.h"

ABaseState::ABaseState()
{

}

void ABaseState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseState, TimeLeft);
}

void ABaseState::BeginPlay()
{
	Super::BeginPlay();
	Logger::Log("Beginning Play Base State...");
	TimeLeft = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	if(ItemDatabase)
	{
		// get row names of the item database
		TArray<FName> RowNames = ItemDatabase->GetRowNames();
		FString ContextString;

		// find the item in the item database that has the same class as ActorClass, 
		// get its ItemID, and create a new UItem that has that ItemID
		for(auto& Name : RowNames)
		{
			FItemStruct * Row = ItemDatabase->FindRow<FItemStruct>(Name, ContextString);
		}
	}
}

void ABaseState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ABaseState::GetTimeLeft()
{
	return TimeLeft;
}

void ABaseState::GameOver_Implementation()
{
	GameOverScreen();
}

UItem * ABaseState::GetItemFromStaticMesh(UStaticMesh * StaticMesh)
{
	checkf(ItemDatabase != nullptr, TEXT("Item Database not set for BaseState"))

	if(!StaticMesh) return nullptr;

	// get row names of the item database
	TArray<FName> RowNames = ItemDatabase->GetRowNames();
	FString ContextString;

	// find the item in the item database that has the same mesh as StaticMesh, 
	// get its ItemID, and create a new UItem that has that ItemID
	for(auto& Name : RowNames)
	{
		FItemStruct * Row = ItemDatabase->FindRow<FItemStruct>(Name, ContextString);
		if(Row && Row->Mesh && StaticMesh->GetName() == Row->Mesh->GetName())
		{
			UItem * NewItem = NewObject<UItem>(this, FName(*Row->Name));
			NewItem->ItemID = Row->ItemID;
			return NewItem;
		}
	}
	return nullptr;
}

UItem * ABaseState::GetItemFromActorClass(AActor * ActorClass)
{
	checkf(ItemDatabase != nullptr, TEXT("Item Database not set for BaseState"))

	if(!ActorClass) return nullptr;

	// get row names of the item database
	TArray<FName> RowNames = ItemDatabase->GetRowNames();
	FString ContextString;

	// find the item in the item database that has the same class as ActorClass, 
	// get its ItemID, and create a new UItem that has that ItemID
	for(auto& Name : RowNames)
	{
		FItemStruct * Row = ItemDatabase->FindRow<FItemStruct>(Name, ContextString);
		if(Row && Row->ActorClass == ActorClass->GetClass())
		{
			UItem * NewItem = NewObject<UItem>(this, FName(*Row->Name));
			NewItem->ItemID = Row->ItemID;
			return NewItem;
		}
	}
	return nullptr;
}

/* Given a UItem, search the ItemDatabase for its associated ActorClass and return it
*/
TSubclassOf<class AActor> ABaseState::GetActorClassFromItem(UItem * Item)
{
	checkf(ItemDatabase != nullptr, TEXT("Item Database not set for BaseState"))

	if(!Item) return nullptr;

	// get row names of the item database
	TArray<FName> RowNames = ItemDatabase->GetRowNames();
	FString ContextString;

	// find the item in the item database that has the same ItemID as Item, 
	// get the class associated with that ItemID, and return that class
	for(auto& Name : RowNames)
	{
		FItemStruct * Row = ItemDatabase->FindRow<FItemStruct>(Name, ContextString);
		if(Item->ItemID == Row->ItemID)
		{
			return Row->ActorClass;
		}
	}
	return nullptr;
}

UStaticMesh * ABaseState::GetMeshFromItem(UItem * Item)
{
	checkf(ItemDatabase != nullptr, TEXT("Item Database not set for BaseState"))

	if(!Item) return nullptr;

	// get row names of the item database
	TArray<FName> RowNames = ItemDatabase->GetRowNames();
	FString ContextString;

	// find the item in the item database that has the same ItemID as Item, 
	// get the class associated with that ItemID, and return that class
	for(auto& Name : RowNames)
	{
		FItemStruct * Row = ItemDatabase->FindRow<FItemStruct>(Name, ContextString);
		if(Item->ItemID == Row->ItemID)
		{
			return Row->Mesh;
		}
	}
	return nullptr;
}


UTexture2D * ABaseState::GetThumbnailFromItem(UItem * Item)
{
	checkf(ItemDatabase != nullptr, TEXT("Item Database not set for BaseState"))

	if(!Item) return nullptr;

	// get row names of the item database
	TArray<FName> RowNames = ItemDatabase->GetRowNames();
	FString ContextString;

	// find the item in the item database that has the same ItemID as Item, 
	// get the class associated with that ItemID, and return that class
	for(auto& Name : RowNames)
	{
		FItemStruct * Row = ItemDatabase->FindRow<FItemStruct>(Name, ContextString);
		if(Item->ItemID == Row->ItemID)
		{
			return Row->Thumbnail;
		}
	}
	return nullptr;
}