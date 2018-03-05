// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "UnrealNetwork.h"
#include "BasePlayerState.h"

ABasePlayerState::ABasePlayerState()
{
	if(HasAuthority())
	{
		Logger::Log("PlayerState: BasePlayerState" + GetName());
		//TimeStart = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	}
}

void ABasePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABasePlayerState, Kills);
	DOREPLIFETIME(ABasePlayerState, Deaths);
	DOREPLIFETIME(ABasePlayerState, Name);
	DOREPLIFETIME(ABasePlayerState, DamageDealt);
	DOREPLIFETIME(ABasePlayerState, DamageTaken);
	DOREPLIFETIME(ABasePlayerState, TimeStart);
	DOREPLIFETIME(ABasePlayerState, CurrentPing);
}

void ABasePlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePlayerState::AddKill(int Kill)
{
	Kills += Kill;
}
void ABasePlayerState::AddDeath(int Death)
{
	Deaths += Death;
}
void ABasePlayerState::AddDamageDealt(float Damage)
{
	DamageDealt += Damage;
}
void ABasePlayerState::AddDamageTaken(float Damage)
{
	DamageTaken += Damage;
}

FString ABasePlayerState::GetName() const { return Name; }
int ABasePlayerState::GetKills() const { return Kills; }
int ABasePlayerState::GetDeaths() const { return Deaths; }
float ABasePlayerState::GetDamageDealt() const { return DamageDealt; }
float ABasePlayerState::GetDamageTaken() const { return DamageTaken; }
void ABasePlayerState::SetName(FString S) 
{ 
	Name = S;
}
