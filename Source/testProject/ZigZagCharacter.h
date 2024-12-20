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

    // �R���g���[���̐ݒ�
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Value); // �O�i
    void Zigzag(); // �֍s����
    void ResetPosition(); // X���W�����ɖ߂�

    FVector StartPosition; // ���̈ʒu���L�^
    bool bIsZigzagging; // �֍s�����ǂ���
    float ZigzagTimer; // �֍s����p�^�C�}�[
};
