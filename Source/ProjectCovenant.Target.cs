// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectCovenantTarget : TargetRules
{
	public ProjectCovenantTarget(TargetInfo Target) : base (Target)
	{
		Type = TargetType.Game;
		
		ExtraModuleNames.Add("ProjectCovenant");
	}

	//
	// TargetRules interface.
	//
}
