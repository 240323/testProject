#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZigZagCharacter.generated.h"

UCLASS()
class YOURPROJECT_API AZigZagCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AZigZagCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // コントロールの設定
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Value); // 前進
    void Zigzag(); // 蛇行動作
    void ResetPosition(); // X座標を元に戻す

    FVector StartPosition; // 元の位置を記録
    bool bIsZigzagging; // 蛇行中かどうか
    float ZigzagTimer; // 蛇行動作用タイマー
};
