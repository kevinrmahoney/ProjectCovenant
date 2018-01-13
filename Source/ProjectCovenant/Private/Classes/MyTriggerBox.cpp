// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCovenant.h"
#include "MyTriggerBox.h"

bool AMyTriggerBox::PrintStatement()
{
	Logger::Log("Called from C++");
	return true;
}