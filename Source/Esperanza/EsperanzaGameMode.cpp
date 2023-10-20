// Copyright Epic Games, Inc. All Rights Reserved.

#include "EsperanzaGameMode.h"
#include "EsperanzaCharacter.h"
#include "Kismet/GameplayStatics.h"//Level関連の関数を使う場合にインクルードする必要がある
#include "UObject/ConstructorHelpers.h"

AEsperanzaGameMode::AEsperanzaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//エスペランサゲームモードでスタートする際に生成するキャラクターをここで選択する（ファイルパス形式）
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AEsperanzaGameMode::RestartEsperanzaGame()
{
	// 現在のLevelNameを取得する
	//FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	FString CurrentLevelName = "ThirdPersonMap";//呼び出すマップ名を文字列で定義する

	// CurrentLevelNameと同じ名前のLevelを開きなおす
	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));
}