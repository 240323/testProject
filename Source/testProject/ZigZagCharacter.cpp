#include "ZigZagCharacter.h"
#include "GameFramework/PlayerController.h"

AZigZagCharacter::AZigZagCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // 初期値の設定
    bIsZigzagging = false;
    ZigzagTimer = 0.0f;
}

void AZigZagCharacter::BeginPlay()
{
    Super::BeginPlay();
    StartPosition = GetActorLocation(); // 初期位置を記録
}

void AZigZagCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsZigzagging)
    {
        ZigzagTimer += DeltaTime;

        // 蛇行中の動き
        FVector NewLocation = GetActorLocation();
        NewLocation.X += 100.0f * DeltaTime; // 前進
        NewLocation.Y += FMath::Sin(ZigzagTimer * 5.0f) * 50.0f; // 蛇行の左右動き
        SetActorLocation(NewLocation);

        // 蛇行が終了したら元の位置に戻る
        if (ZigzagTimer > 2.0f)
        {
            bIsZigzagging = false;
            ZigzagTimer = 0.0f;
            ResetPosition();
        }
    }
}

void AZigZagCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 入力をバインド
    PlayerInputComponent->BindAxis("MoveForward", this, &AZigZagCharacter::MoveForward);
}

void AZigZagCharacter::MoveForward(float Value)
{
    if (Value > 0.0f) // 前進入力があった場合
    {
        FVector Forward = GetActorForwardVector();
        AddMovementInput(Forward, Value);

        // 障害物が近づいたら蛇行を開始
        FVector CurrentLocation = GetActorLocation();
        if (FVector::Dist(CurrentLocation, StartPosition) > 500.0f) // 障害物との距離
        {
            bIsZigzagging = true;
        }
    }
}

void AZigZagCharacter::ResetPosition()
{
    // 元のX座標に戻る
    FVector CurrentLocation = GetActorLocation();
    CurrentLocation.X = StartPosition.X;
    SetActorLocation(CurrentLocation);
}
