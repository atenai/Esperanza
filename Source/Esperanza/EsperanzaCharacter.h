#pragma once // このヘッダーファイルが1回だけ読み込まれるようにする

#include "CoreMinimal.h" // Unreal Engineでよく使う基本的な型や機能を読み込む
#include "GameFramework/Character.h" // ACharacterクラスを使うためのヘッダーを読み込む
#include "InputMappingContext.h" // Enhanced Inputの入力マッピングコンテキストを使うためのヘッダーを読み込む
#include "InputAction.h" // Enhanced Inputの入力アクションを使うためのヘッダーを読み込む
#include "InputActionValue.h" // 入力アクションの値を受け取るためのヘッダーを読み込む
#include "EsperanzaCharacter.generated.h" // Unreal Header Toolが生成するコードを読み込む


UCLASS(config = Game) // このクラスをUnreal EngineのUClassとして登録し、Game設定を使えるようにする
class AEsperanzaCharacter : public ACharacter // ACharacterを継承したAEsperanzaCharacterクラスを定義する
{
	GENERATED_BODY() // Unreal EngineのリフレクションやBlueprint連携に必要なコードを生成する

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) // エディタで表示可能、Blueprintで読み取り可能、Cameraカテゴリに表示し、privateでもBlueprintからアクセス可能にする
		class USpringArmComponent* CameraBoom; // キャラクターとカメラの距離を保つためのスプリングアームコンポーネント

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) // エディタで表示可能、Blueprintで読み取り可能、Cameraカテゴリに表示し、privateでもBlueprintからアクセス可能にする
		class UCameraComponent* FollowCamera; // キャラクターを追従するカメラコンポーネント

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) // エディタで編集可能、Blueprintで読み取り可能、Inputカテゴリに表示し、privateでもBlueprintからアクセス可能にする
		class UInputMappingContext* DefaultMappingContext; // デフォルトで使用するEnhanced Inputの入力マッピング設定

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) // エディタで編集可能、Blueprintで読み取り可能、Inputカテゴリに表示し、privateでもBlueprintからアクセス可能にする
		class UInputAction* MoveAction; // 移動入力に対応するInputAction

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) // エディタで編集可能、Blueprintで読み取り可能、Inputカテゴリに表示し、privateでもBlueprintからアクセス可能にする
		class UInputAction* LookAction; // カメラ操作、視点操作に対応するInputAction

public: // 外部のクラスからアクセスできるメンバをここから定義する
	AEsperanzaCharacter(); // AEsperanzaCharacterクラスのコンストラクタ宣言

	//①このように書くことで、ブループリントエディタのキャラクターの詳細設定にアニメーションをアタッチする項目が出現する
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations) // エディタで編集可能、Blueprintで読み書き可能、Animationsカテゴリに表示する
	//UAnimMontage* M_punch; // パンチ用のアニメーションモンタージュを保持する変数

	//②関数を作成する
	//void Punch(); // パンチ処理を行う関数の宣言

protected: // このクラス自身と子クラスからアクセスできるメンバをここから定義する

	void Move(const FInputActionValue& Value); // 移動入力の値を受け取り、キャラクターを移動させる関数

	void Look(const FInputActionValue& Value); // 視点入力の値を受け取り、カメラや視点を回転させる関数


protected: // このクラス自身と子クラスからアクセスできるメンバをここから定義する
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // 入力設定を行う関数を親クラスからオーバーライドする

	virtual void BeginPlay(); // ゲーム開始時やActor生成時に呼ばれるBeginPlay関数を宣言する

public: // 外部のクラスからアクセスできるメンバをここから定義する
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; } // CameraBoomを取得するためのインライン関数
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; } // FollowCameraを取得するためのインライン関数
};