// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "HealthPack.h"
#include "SubjectZero.h"

bool AHealthPack::AddHealth(ASubjectZero * player, float HealthBoost) {
	player->IncreaseHealth(0.25f);
	return true;
}
