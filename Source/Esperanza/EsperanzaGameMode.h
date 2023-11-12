// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EsperanzaGameMode.generated.h"

UCLASS(minimalapi)
class AEsperanzaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEsperanzaGameMode();

public:
	UFUNCTION(BlueprintCallable, Category = "KashiwabaraYuuta")
	void TitleTransition();
};



