// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HealthPack.h"
#include "SubjectZero.h"

bool AHealthPack::AddHealth(ASubjectZero * player) {
	if(HasAuthority())
	{
		player->IncreaseHealth(HealthBoostPercentage);
	}
		return true;
}
