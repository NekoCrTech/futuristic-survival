// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FuturisticSurvival : ModuleRules
{
	public FuturisticSurvival(ReadOnlyTargetRules Target) : base(Target)
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
			"FuturisticSurvival",
			"FuturisticSurvival/Variant_Platforming",
			"FuturisticSurvival/Variant_Platforming/Animation",
			"FuturisticSurvival/Variant_Combat",
			"FuturisticSurvival/Variant_Combat/AI",
			"FuturisticSurvival/Variant_Combat/Animation",
			"FuturisticSurvival/Variant_Combat/Gameplay",
			"FuturisticSurvival/Variant_Combat/Interfaces",
			"FuturisticSurvival/Variant_Combat/UI",
			"FuturisticSurvival/Variant_SideScrolling",
			"FuturisticSurvival/Variant_SideScrolling/AI",
			"FuturisticSurvival/Variant_SideScrolling/Gameplay",
			"FuturisticSurvival/Variant_SideScrolling/Interfaces",
			"FuturisticSurvival/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
