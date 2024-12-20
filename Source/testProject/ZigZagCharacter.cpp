#include "ZigZagCharacter.h"
#include "GameFramework/PlayerController.h"

AZigZagCharacter::AZigZagCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // �����l�̐ݒ�
    bIsZigzagging = false;
    ZigzagTimer = 0.0f;
}

void AZigZagCharacter::BeginPlay()
{
    Super::BeginPlay();
    StartPosition = GetActorLocation(); // �����ʒu���L�^
}

void AZigZagCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsZigzagging)
    {
        ZigzagTimer += DeltaTime;

        // �֍s���̓���
        FVector NewLocation = GetActorLocation();
        NewLocation.X += 100.0f * DeltaTime; // �O�i
        NewLocation.Y += FMath::Sin(ZigzagTimer * 5.0f) * 50.0f; // �֍s�̍��E����
        SetActorLocation(NewLocation);

        // �֍s���I�������猳�̈ʒu�ɖ߂�
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

    // ���͂��o�C���h
    PlayerInputComponent->BindAxis("MoveForward", this, &AZigZagCharacter::MoveForward);
}

void AZigZagCharacter::MoveForward(float Value)
{
    if (Value > 0.0f) // �O�i���͂��������ꍇ
    {
        FVector Forward = GetActorForwardVector();
        AddMovementInput(Forward, Value);

        // ��Q�����߂Â�����֍s���J�n
        FVector CurrentLocation = GetActorLocation();
        if (FVector::Dist(CurrentLocation, StartPosition) > 500.0f) // ��Q���Ƃ̋���
        {
            bIsZigzagging = true;
        }
    }
}

void AZigZagCharacter::ResetPosition()
{
    // ����X���W�ɖ߂�
    FVector CurrentLocation = GetActorLocation();
    CurrentLocation.X = StartPosition.X;
    SetActorLocation(CurrentLocation);
}
