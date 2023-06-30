// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TestMyActor.h"
#include "Kismet/KismetSystemLibrary.h" //�ǉ�

// Sets default values
ACPP_TestMyActor::ACPP_TestMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_TestMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// PrintString�m�[�h�Ɠ�������
	// UKismetSystemLibrary�N���X��PrintString�֐����Ăяo��
	UKismetSystemLibrary::PrintString(this, "C++ Esperanza Start!!", true, true, FColor::Red, 100.f, TEXT("None"));
}

// Called every frame
void ACPP_TestMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

