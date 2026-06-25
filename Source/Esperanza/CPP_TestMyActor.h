#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_TestMyActor.generated.h"

UCLASS()
class ESPERANZA_API ACPP_TestMyActor : public AActor
{
	GENERATED_BODY()

public:
	ACPP_TestMyActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
