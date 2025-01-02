// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EsperanzaEditorTarget : TargetRules
{
	public EsperanzaEditorTarget(TargetInfo Target) : base(Target)
	{
        Type = TargetType.Editor;

        // �ŐV�̃r���h�ݒ�o�[�W�������g�p
        DefaultBuildSettings = BuildSettingsVersion.V5;

        // �ŐV��Include Order���g�p
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        // ���W���[������ǉ�
        ExtraModuleNames.Add("Esperanza");
    }
}
