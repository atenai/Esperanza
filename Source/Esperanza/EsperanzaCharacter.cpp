#include "EsperanzaCharacter.h" // AEsperanzaCharacterクラスの宣言が書かれているヘッダーファイルを読み込む
#include "Camera/CameraComponent.h" // カメラコンポーネントを使用するためのヘッダーを読み込む
#include "Components/CapsuleComponent.h" // カプセルコリジョンコンポーネントを使用するためのヘッダーを読み込む
#include "Components/InputComponent.h" // 入力コンポーネントを使用するためのヘッダーを読み込む
#include "GameFramework/CharacterMovementComponent.h" // キャラクターの移動制御コンポーネントを使用するためのヘッダーを読み込む
#include "GameFramework/Controller.h" // Controllerクラスを使用するためのヘッダーを読み込む
#include "GameFramework/SpringArmComponent.h" // カメラアームであるSpringArmComponentを使用するためのヘッダーを読み込む
#include "EnhancedInputComponent.h" // Enhanced Input用の入力コンポーネントを使用するためのヘッダーを読み込む
#include "EnhancedInputSubsystems.h" // Enhanced Inputのサブシステムを使用するためのヘッダーを読み込む



/// <summary>
/// コンストラクタ
/// </summary>
AEsperanzaCharacter::AEsperanzaCharacter() // AEsperanzaCharacterクラスのコンストラクタ
{
	// カプセルコリジョンを設定
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f); // キャラクターの当たり判定となるカプセルの半径を42、高さを96に設定する

	bUseControllerRotationPitch = false; // コントローラーの上下回転をキャラクター本体には反映しない
	bUseControllerRotationYaw = false; // コントローラーの左右回転をキャラクター本体には直接反映しない
	bUseControllerRotationRoll = false; // コントローラーの傾き回転をキャラクター本体には反映しない


	GetCharacterMovement()->bOrientRotationToMovement = true; // 移動方向に合わせてキャラクターの向きを自動で回転させる
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // キャラクターが移動方向へ向きを変える回転速度を設定する

	GetCharacterMovement()->AirControl = 0.35f; // 空中での移動操作の効きやすさを設定する
	GetCharacterMovement()->MaxWalkSpeed = 500.f; // 通常歩行時の最大移動速度を設定する
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f; // アナログ入力時の最小歩行速度を設定する
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; // 歩行中に停止するときの減速の強さを設定する

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")); // CameraBoomという名前でSpringArmComponentを作成する
	CameraBoom->SetupAttachment(RootComponent); // CameraBoomをキャラクターのRootComponentにアタッチする
	CameraBoom->TargetArmLength = 400.0f; // キャラクターからカメラまでの距離を400に設定する
	CameraBoom->bUsePawnControlRotation = true; // コントローラーの回転に合わせてCameraBoomを回転させる

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); // FollowCameraという名前でカメラコンポーネントを作成する
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // カメラをCameraBoomの先端ソケットにアタッチする
	FollowCamera->bUsePawnControlRotation = false; // カメラ自体はPawnの回転を直接使わないようにする
}

/// <summary>
/// スタート関数
/// </summary>
void AEsperanzaCharacter::BeginPlay() // ゲーム開始時、またはキャラクター生成時に最初に呼ばれる関数
{
	//親クラスのスタート関数を呼ぶ
	Super::BeginPlay(); // 親クラスであるACharacterのBeginPlay処理を実行する

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) // ControllerをAPlayerController型にキャストし、成功した場合だけ処理を行う
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) // ローカルプレイヤーからEnhanced Input用のサブシステムを取得する
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0); // デフォルトの入力マッピングコンテキストを優先度0で追加する
		}
	}
}


void AEsperanzaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) // プレイヤーの入力設定を行う関数
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) // 通常のInputComponentをEnhancedInputComponentとして取得する
	{
		//移動
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEsperanzaCharacter::Move); // MoveActionが入力されたとき、自作のMove関数を呼ぶ

		//カメラ
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEsperanzaCharacter::Look); // LookActionが入力されたとき、自作のLook関数を呼ぶ
	}

	//③ボタンが押されたらアニメーションを再生する関数を追加
	//PlayerInputComponent->BindAction("Punch", IE_Pressed, this, &AEsperanzaCharacter::Punch); // Punch入力が押されたとき、Punch関数を呼ぶ予定の処理
}

void AEsperanzaCharacter::Move(const FInputActionValue& Value) // 移動入力を受け取ってキャラクターを移動させる関数
{
	FVector2D MovementVector = Value.Get<FVector2D>(); // 入力値を2Dベクトルとして取得する

	if (Controller != nullptr) // Controllerが存在する場合だけ処理を行う
	{
		const FRotator Rotation = Controller->GetControlRotation(); // コントローラーの現在の回転角度を取得する
		const FRotator YawRotation(0, Rotation.Yaw, 0); // 上下回転や傾きは無視して、左右方向のYaw回転だけを取り出す

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // Yaw回転を基準にした前方向ベクトルを取得する

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // Yaw回転を基準にした右方向ベクトルを取得する

		AddMovementInput(ForwardDirection, MovementVector.Y); // 入力のY方向の値を使って前後移動を行う
		AddMovementInput(RightDirection, MovementVector.X); // 入力のX方向の値を使って左右移動を行う
	}
}

void AEsperanzaCharacter::Look(const FInputActionValue& Value) // 視点操作の入力を受け取ってカメラを回転させる関数
{
	FVector2D LookAxisVector = Value.Get<FVector2D>(); // 入力値を2Dベクトルとして取得する

	if (Controller != nullptr) // Controllerが存在する場合だけ処理を行う
	{
		AddControllerYawInput(LookAxisVector.X); // 入力のX方向の値を使って左右に視点を回転させる
		AddControllerPitchInput(LookAxisVector.Y); // 入力のY方向の値を使って上下に視点を回転させる
	}
}

//②アニメーションを再生する関数を作成する
//void AEsperanzaCharacter::Punch() // パンチアニメーションを再生するための関数
//{
//	if (M_punch) // パンチ用のアニメーションモンタージュが設定されているか確認する
//	{
//		//アニメーションを作成する
//		PlayAnimMontage(M_punch, 1, NAME_None); // M_punchのアニメーションモンタージュを再生速度1倍で再生する
//	}
//}