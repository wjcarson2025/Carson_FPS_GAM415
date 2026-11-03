// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Carson_FPS_GAM415 : ModuleRules
{
	public Carson_FPS_GAM415(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
