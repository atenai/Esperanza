#include "CPP_TestMyActor.h"
#include "Kismet/KismetSystemLibrary.h" //追加

ACPP_TestMyActor::ACPP_TestMyActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACPP_TestMyActor::BeginPlay()
{
	Super::BeginPlay();

	// PrintStringノードと同じ処理
	// UKismetSystemLibraryクラスのPrintString関数を呼び出す
	UKismetSystemLibrary::PrintString(this, "C++ Esperanza Start!!", true, true, FColor::Red, 100.f, TEXT("None"));
}

void ACPP_TestMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

