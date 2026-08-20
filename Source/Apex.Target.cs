using UnrealBuildTool;
public class ApexTarget : TargetRules { public ApexTarget(TargetInfo Target) : base(Target) { Type = TargetType.Game; DefaultBuildSettings = BuildSettingsVersion.V5; ExtraModuleNames.Add("Apex"); } }
