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
			"Niagara",
			"Slate",
			"GameplayAbilities",
			"GameplayTasks",
			"GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });
	
		// ✅ This line disables Windows min/max macros permanently
		PublicDefinitions.Add("NOMINMAX");
		
		PublicIncludePaths.AddRange(new string[] {
			"FuturisticSurvival",
		});
	}
}
