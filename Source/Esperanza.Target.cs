// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EsperanzaTarget : TargetRules
{
	public EsperanzaTarget(TargetInfo Target) : base(Target)
	{
        Type = TargetType.Game;

        DefaultBuildSettings = BuildSettingsVersion.V5;

        // �ŐV��Include Order���g�p
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        // ���W���[������ǉ�
        ExtraModuleNames.Add("Esperanza");
    }
}
