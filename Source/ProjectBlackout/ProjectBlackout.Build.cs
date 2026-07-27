using UnrealBuildTool;

public class ProjectBlackout : ModuleRules
{
	public ProjectBlackout(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"OnlineSubsystem",
			"OnlineSubsystemUtils",
			"PhysicsCore",
			"NavigationSystem",
			"Slate",
			"SlateCore",
			"GameplayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"OnlineSubsystemSteam"
		});
	}
}
