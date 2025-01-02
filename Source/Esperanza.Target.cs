// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EsperanzaTarget : TargetRules
{
	public EsperanzaTarget(TargetInfo Target) : base(Target)
	{
        Type = TargetType.Game;

        DefaultBuildSettings = BuildSettingsVersion.V5;

        // 最新のInclude Orderを使用
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        // モジュール名を追加
        ExtraModuleNames.Add("Esperanza");
    }
}
