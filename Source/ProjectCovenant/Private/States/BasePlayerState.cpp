// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "UnrealNetwork.h"
#include "BasePlayerState.h"

ABasePlayerState::ABasePlayerState()
{
	if(HasAuthority())
	{
		Logger::Log("PlayerState: BasePlayerState");
		TimeStart = UGameplayStatics::GetRealTimeSeconds(GetWorld());
		Logger::Log(TimeStart);
	}
}

void ABasePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABasePlayerState, Kills);
	DOREPLIFETIME(ABasePlayerState, DamageDealt);
	DOREPLIFETIME(ABasePlayerState, DamageTaken);
	DOREPLIFETIME(ABasePlayerState, TimeStart);
	DOREPLIFETIME(ABasePlayerState, CurrentPing);
}

void ABasePlayerState::AddKill(int Kill)
{
	Kills += Kill;
	Logger::Log(Kill);
}
void ABasePlayerState::AddDamageDealt(float Damage)
{
	DamageDealt += Damage;
}
void ABasePlayerState::AddDamageTaken(float Damage)
{
	DamageTaken += Damage;
}

int ABasePlayerState::GetKills() const { return Kills; }
float ABasePlayerState::GetDamageDealt() const { return DamageDealt; }
float ABasePlayerState::GetDamageTaken() const { return DamageTaken;  }