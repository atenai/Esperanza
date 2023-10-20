// Copyright Epic Games, Inc. All Rights Reserved.

#include "EsperanzaGameMode.h"
#include "EsperanzaCharacter.h"
#include "Kismet/GameplayStatics.h"//Level�֘A�̊֐����g���ꍇ�ɃC���N���[�h����K�v������
#include "UObject/ConstructorHelpers.h"

AEsperanzaGameMode::AEsperanzaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//�G�X�y�����T�Q�[�����[�h�ŃX�^�[�g����ۂɐ�������L�����N�^�[�������őI������i�t�@�C���p�X�`���j
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AEsperanzaGameMode::RestartEsperanzaGame()
{
	// ���݂�LevelName���擾����
	//FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	FString CurrentLevelName = "ThirdPersonMap";//�Ăяo���}�b�v���𕶎���Œ�`����

	// CurrentLevelName�Ɠ������O��Level���J���Ȃ���
	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));
}