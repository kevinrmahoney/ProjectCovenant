// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HumanController.h"
#include "Spectator.h"
#include "SubjectZero.h"
#include "BasePlayerState.h"
#include "Item.h"
#include "BaseMode.h"
#include "Inventory.h"

ABaseMode::ABaseMode()
{
	// 200% Damage
	HitBoxDamage.Add("HitBoxHead", 2.f);

	// 100% Damage
	HitBoxDamage.Add("HitBoxTorso", 1.f);

	// 75% Damage
	HitBoxDamage.Add("HitBoxLeftUpperarm", 0.75f);
	HitBoxDamage.Add("HitBoxRightUpperarm", 0.75f);
	HitBoxDamage.Add("HitBoxLeftThigh", 0.75f);
	HitBoxDamage.Add("HitBoxRightThigh", 0.75f);

	// 50% Damage
	HitBoxDamage.Add("HitBoxLeftLowerArm", 0.5f);
	HitBoxDamage.Add("HitBoxRightLowerArm", 0.5f);
	HitBoxDamage.Add("HitBoxLeftCalf", 0.5f);
	HitBoxDamage.Add("HitBoxLeftFoot", 0.5f);
	HitBoxDamage.Add("HitBoxRightFoot", 0.5f);
	HitBoxDamage.Add("HitBoxRightCalf", 0.5f);
}

void ABaseMode::BeginPlay()
{
	Super::BeginPlay();
	Logger::Log("Begin BaseMode");
}

void ABaseMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	Logger::Chat("Welcome " + NewPlayer->GetNetOwningPlayer()->GetName());
	Logger::Log(NewPlayer->GetNetOwningPlayer()->GetName() + " has joined the game.");

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), SpawnPoints);
	if(AHumanController * Controller = Cast<AHumanController>(NewPlayer))
	{
		ASpectator * NewPawn;
		if(SpawnPoints.Num() > 0)
		{
			NewPawn = GetWorld()->SpawnActor<ASpectator>(SpawnPoints[SpawnCount]->GetActorLocation(), SpawnPoints[SpawnCount]->GetActorRotation());
		}
		else
		{
			NewPawn = GetWorld()->SpawnActor<ASpectator>(FVector::ZeroVector, FRotator::ZeroRotator);
		}
		Controller->Possess(NewPawn);
	}

	if(SpawnPoints.Num() != 0)
	{
		SpawnCount = (SpawnCount + 1) % SpawnPoints.Num();
	}
}

/* SpawnPlayer() - Spawns a character at a PlayerStart location.
Spawn location rotates over the course of the game
*/
void ABaseMode::SpawnPlayer(AHumanController * Controller)
{
	Logger::Log("Attempting to spawn player " + Controller->GetNetOwningPlayer()->GetName() + " as a SubjectZero");
	if(Controller)
	{
		if(GetWorld())
		{
			ASubjectZero * NewPawn;
			if(SpawnPoints.Num())
			{
				NewPawn = GetWorld()->SpawnActor<ASubjectZero>(SubjectZeroBlueprint, SpawnPoints[SpawnCount]->GetActorLocation(), SpawnPoints[SpawnCount]->GetActorRotation());
				Logger::Log("Spawned player " + Controller->GetNetOwningPlayer()->GetName() + " (" + NewPawn->GetActorLocation().ToString() + ")");
			}
			else
			{
				NewPawn = GetWorld()->SpawnActor<ASubjectZero>(SubjectZeroBlueprint, FVector::ZeroVector, FRotator::ZeroRotator);
				Logger::Log("Spawned player " + Controller->GetNetOwningPlayer()->GetName() + " (" + NewPawn->GetActorLocation().ToString() + ")");
			}
			Characters.Add(NewPawn);

			APawn * OldPawn = Controller->GetPawn();
			Controller->Possess(NewPawn);
			if(OldPawn) OldPawn->Destroy();
		}
	}

	if(SpawnPoints.Num() != 0)
	{
		SpawnCount = (SpawnCount + 1) % SpawnPoints.Num();
	}
}

void ABaseMode::KillPlayer(AHumanController * Controller)
{
	if(Controller)
	{
		if(GetWorld())
		{
			if(APawn * OldPawn = Controller->AcknowledgedPawn)
			{
				ASpectator * NewPawn = GetWorld()->SpawnActor<ASpectator>(OldPawn->GetActorLocation(), OldPawn->GetActorRotation());
				Controller->Possess(NewPawn);
				if(ASubjectZero * SubjectZero = Cast<ASubjectZero>(OldPawn))
				{
					Characters.Remove(SubjectZero);
					Logger::Log("Killing player " + SubjectZero->GetName());
					SubjectZero->Kill();
				}
			}
		}
	}
}

float ABaseMode::CalculateLocationalDamage(float BaseDamage, UPrimitiveComponent * HitBox)
{
	if(HitBox)
	{
		if(HitBoxDamage.Contains(HitBox->GetName()))
		{
			float HitBoxMultiplier = *HitBoxDamage.Find(HitBox->GetName());
			BaseDamage = BaseDamage * HitBoxMultiplier;
		}
	}
	return BaseDamage;
}

void ABaseMode::DealDamage(ASubjectZero * Shooter, ASubjectZero * Victim, float Damage, AWeapon * Weapon, UPrimitiveComponent * HitBox)
{
	// Multiply raw damage by multiplier
	Damage = CalculateLocationalDamage(Damage, HitBox);
	Damage = Shooter ? Shooter->GetDamageMultiplier() * Damage : Damage;

	bool Killed = false;

	// Deal damage to the victim, returns if the player was killed by the damage
	if(Victim)
	{
		if(AHumanController * VictimController = Cast<AHumanController>(Victim->GetController()))
		{
			if(VictimController && VictimController->GodMode == false)
			{
				Killed = Victim->ReceiveDamage(Damage, Victim == Shooter);
			}
		}
	}

	// Log the damage and if the player was killed by it
	FString ShooterName = Shooter ? Shooter->GetPlayerName().ToString() : "Server";
	FString VictimName = Victim ? Victim->GetPlayerName().ToString() : "Unknown";
	FString WeaponName = Weapon ? Weapon->GetName() : "large fluffy pants";

	Logger::Log(ShooterName + " has dealt " + FString::SanitizeFloat(Damage) + " to " + VictimName + " using " + WeaponName);
	if(Killed) Logger::Log(ShooterName + " has killed " + VictimName + " using " + WeaponName);


	// Obtain the player states for the shooter and the victim
	if(Shooter)
	{
		ABasePlayerState * ShooterPlayerState = Cast<ABasePlayerState>(Shooter->PlayerState);

		// If the player state is successfully obtained, add the damage that was dealt to the player state, and if killed, add the kill
		if(ShooterPlayerState)
		{
			ShooterPlayerState->AddDamageDealt(Damage);
			ShooterPlayerState->DealtDamage(Damage);
			if(Killed) ShooterPlayerState->AddKill(1);
		}
	}
	else
	{
		Logger::Error("Could not cast or obtain shooter's PlayerState");
	}

	// If there was a victim of the damage
	if(Victim)
	{
		ABasePlayerState * VictimPlayerState = Cast<ABasePlayerState>(Victim->PlayerState);
		// If the player state is successfully obtained, add the damage that was dealt to the player state, and if killed, add the kill
		if(VictimPlayerState)
		{
			VictimPlayerState->AddDamageTaken(Damage);
			VictimPlayerState->TookDamage(Damage);
			if(Killed) VictimPlayerState->AddDeath(1);
		}
		else
		{
			Logger::Error("Could not cast or obtain victim's PlayerState");
		}

		// If that victim was killed after damage was dealt
		if(Killed)
		{

			// Kill the player, and drop his items on the ground
			if(AHumanController * HumanController = Cast<AHumanController>(Victim->GetController()))
			{
				TArray<UItem*> Items = Victim->GetInventory()->GetItems();
				for(UItem * Item : Items)
				{
					// Spawn an actor of the type associated with the item, a random distance from the victim
					FVector RandomOffset = FVector(FMath::FRandRange(-100.f, 100.f), FMath::FRandRange(-100.f, 100.f), 0.f);

					// If the weapon was created successfully, drop it (sets gravity, collision and physics on) and give it a slight velocity relative to the victim's velocity
					if(Item)
					{
						DropItem(Item, Victim->GetActorLocation() + RandomOffset, Victim->GetVelocity());
						Logger::Log("Dropping weapon " + Item->ItemID.ToString() + " from death of " + Victim->GetName() + " (" + Victim->GetActorLocation().ToString() + ")");
					}
					else
					{
						Logger::Error("Failed to drop item " + GetActorClass(Item).GetDefaultObject()->GetName() + " from inventory of dead " + Victim->GetName());
					}
				}
				KillPlayer(HumanController);
			}
			else
			{
				Logger::Log("Could not kill player " + Victim->GetName());
			}
		}
	}
}

void ABaseMode::DropItem(UItem * Item, FVector Position, FVector Velocity)
{
	UStaticMesh * StaticMesh = nullptr;

	// Get the static mesh related to the Item
	TArray<FName> RowNames = ItemDatabase->GetRowNames();
	FString ContextString;
	if(Item)
	{
		for(auto& Name : RowNames)
		{
			FItemStruct * Row = ItemDatabase->FindRow<FItemStruct>(Name, ContextString);
			if(Item->ItemID == Row->ItemID)
			{
				StaticMesh = Row->Mesh;
			}
		}
	}

	check(StaticMesh != nullptr)

	AInteractable * Interactable = GetWorld()->SpawnActor<AInteractable>(Position, FRotator(0.f, 0.f, 0.f));
	Interactable->SetMesh(StaticMesh);
	Interactable->GetStaticMeshComponent()->AddImpulse(Velocity);
}

void ABaseMode::GiveItemToCharacter(ASubjectZero * Character, UItem * Item)
{
	if(Item && Character)
	{
		Character->AddItemToInventory(Item);
		Logger::Log("Gave character " + Character->GetName() + " weapon " + Item->GetName());
	}
}

void ABaseMode::GiveStartingInventory(ASubjectZero * Character)
{
	if(Character)
	{
		UItem * LightningGun = NewObject<UItem>(this, "LightningGun");
		LightningGun->ItemID = TEXT("0");
		GiveItemToCharacter(Character, LightningGun);
		UItem * Shotgun = NewObject<UItem>(this, "Shotgun");
		//Shotgun->ItemID = TEXT("1");
		//GiveItemToCharacter(Character, Shotgun);
		//UItem * Railgun = NewObject<UItem>(this, "Railgun");
		//Railgun->ItemID = TEXT("2");
		//GiveItemToCharacter(Character, Railgun);
		//UItem * RocketLauncher = NewObject<UItem>(this, "RocketLauncher");
		//RocketLauncher->ItemID = TEXT("3");
		//GiveItemToCharacter(Character, RocketLauncher);
		//UItem * Rifle = NewObject<UItem>(this, "Rifle");
		//Rifle->ItemID = TEXT("4");
		//GiveItemToCharacter(Character, Rifle);
		//UItem * SniperRifle = NewObject<UItem>(this, "SniperRifle");
		//SniperRifle->ItemID = TEXT("5");
		//GiveItemToCharacter(Character, SniperRifle);
		//UItem * Carbine = NewObject<UItem>(this, "Carbine");
		//Carbine->ItemID = TEXT("6");
		//GiveItemToCharacter(Character, Carbine);
		//UItem * Cannon = NewObject<UItem>(this, "Cannon");
		//Cannon->ItemID = TEXT("7");
		//GiveItemToCharacter(Character, Cannon);
	}
}

UItem * ABaseMode::GetItem(UStaticMesh * StaticMesh)
{
	TArray<FName> RowNames = ItemDatabase->GetRowNames();
	FString ContextString;

	if(StaticMesh)
	{
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
	}
	return nullptr;
}

// Given a AWeapon, create an associated UItem based on information in the ItemDatabase
UItem * ABaseMode::GetItem(AWeapon * ActorClass)
{
	TArray<FName> RowNames = ItemDatabase->GetRowNames();
	FString ContextString;

	if(ActorClass)
	{
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
	}
	return nullptr;
}

TSubclassOf<class AActor> ABaseMode::GetActorClass(UItem * Item)
{
	TArray<FName> RowNames = ItemDatabase->GetRowNames();
	FString ContextString;

	if(Item)
	{
		for(auto& Name : RowNames)
		{
			FItemStruct * Row = ItemDatabase->FindRow<FItemStruct>(Name, ContextString);
			if(Item->ItemID == Row->ItemID)
			{
				return Row->ActorClass;
			}
		}
	}
	return nullptr;
}

