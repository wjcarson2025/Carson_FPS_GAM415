// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Carson_FPS_GAM415 : ModuleRules
{
	public Carson_FPS_GAM415(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Carson_FPS_GAM415",
			"Carson_FPS_GAM415/Variant_Horror",
			"Carson_FPS_GAM415/Variant_Horror/UI",
			"Carson_FPS_GAM415/Variant_Shooter",
			"Carson_FPS_GAM415/Variant_Shooter/AI",
			"Carson_FPS_GAM415/Variant_Shooter/UI",
			"Carson_FPS_GAM415/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
