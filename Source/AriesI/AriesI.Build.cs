// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class AriesI : ModuleRules
{
	public AriesI(TargetInfo Target)
	{
        PrivateIncludePaths.AddRange(
            new string[] {
                "AriesI/GameCore",
                "AriesI/GameCore/AI",
                "AriesI/GameData",
                "AriesI/Characters",
                "AriesI/Characters/Enemies",
                "AriesI/GameItems"
            }
        );

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Paper2D", "AIModule" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true


    }
}
