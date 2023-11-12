// Copyright Epic Games, Inc. All Rights Reserved.

#include "EsperanzaGameMode.h"
#include "EsperanzaCharacter.h"
#include "Kismet/GameplayStatics.h"//Level関連の関数を使う場合にインクルードする必要がある
#include "UObject/ConstructorHelpers.h"

AEsperanzaGameMode::AEsperanzaGameMode()
{
	//デフォルトポーンキャラクターを指定する
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//エスペランサゲームモードでスタートする際に生成するキャラクターをここで選択する（ファイルパス形式）
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
	//現在のLevelNameを取得する
	//FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	FString LevelName = "Title";//呼び出すマップ名を文字列で定義する

	//LevelNameと同じ名前のLevelを開きなおす
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
}