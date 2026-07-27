using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectBlackoutEditorTarget : TargetRules
{
	public ProjectBlackoutEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("ProjectBlackout");
	}
}
