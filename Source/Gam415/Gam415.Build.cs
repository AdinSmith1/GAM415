// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gam415 : ModuleRules
{
	public Gam415(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Niagara", "ProceduralMeshComponent" });
	}
}
