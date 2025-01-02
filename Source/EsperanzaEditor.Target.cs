// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EsperanzaEditorTarget : TargetRules
{
	public EsperanzaEditorTarget(TargetInfo Target) : base(Target)
	{
        Type = TargetType.Editor;

        // 最新のビルド設定バージョンを使用
        DefaultBuildSettings = BuildSettingsVersion.V5;

        // 最新のInclude Orderを使用
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        // モジュール名を追加
        ExtraModuleNames.Add("Esperanza");
    }
}
