// Copyright Epic Games, Inc. All Rights Reserved.

#include "EsperanzaGameMode.h"
#include "EsperanzaCharacter.h"
#include "Kismet/GameplayStatics.h"//Level�֘A�̊֐����g���ꍇ�ɃC���N���[�h����K�v������
#include "UObject/ConstructorHelpers.h"

AEsperanzaGameMode::AEsperanzaGameMode()
{
	//�f�t�H���g�|�[���L�����N�^�[���w�肷��
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//�G�X�y�����T�Q�[�����[�h�ŃX�^�[�g����ۂɐ�������L�����N�^�[�������őI������i�t�@�C���p�X�`���j
	static ConstructorHelpers::FClassFinder<APawn> BP_PlayerPawnClass(TEXT("/Game/Esperanza/Blueprints/Player/BP_Player.BP_Player_C"));
	if (BP_PlayerPawnClass.Class != NULL)
	{
		DefaultPawnClass = BP_PlayerPawnClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> BP_PlayerControllerClass(TEXT("/Game/Esperanza/Blueprints/InGame/PC_Esperanza.PC_Esperanza_C"));
	if (BP_PlayerControllerClass.Class != NULL)
	{
		PlayerControllerClass = BP_PlayerControllerClass.Class;
	}

	UClass* BP_HUDClass = LoadObject<UClass>(nullptr, TEXT("/Game/Esperanza/Blueprints/InGame/HUD_Esperanza.HUD_Esperanza_C"));
	if (BP_HUDClass != NULL)
	{
		HUDClass = BP_HUDClass;
	}
}

void AEsperanzaGameMode::GameOverTransition()
{
	//���݂�LevelName���擾����
	//FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	FString LevelName = "Title";//�Ăяo���}�b�v���𕶎���Œ�`����

	//LevelName�Ɠ������O��Level���J���Ȃ���
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
}