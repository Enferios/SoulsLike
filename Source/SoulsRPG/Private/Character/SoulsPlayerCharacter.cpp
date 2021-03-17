// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SoulsPlayerCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"


ASoulsPlayerCharacter::ASoulsPlayerCharacter()
{
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
    GetCharacterMovement()->MaxWalkSpeed = 500.f;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
    SpringArm->TargetArmLength = 300.f;
    SpringArm->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject <UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(SpringArm, SpringArm->SocketName);

    TurnRate = 60.f;
    LookUpRate = 60.f;
   
}

void ASoulsPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Turn", this, &ASoulsPlayerCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &ASoulsPlayerCharacter::LookUp);

    PlayerInputComponent->BindAxis("MoveForward", this, &ASoulsPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASoulsPlayerCharacter::MoveRight);
}

void ASoulsPlayerCharacter::MoveForward(float AxisValue)
{
    bool bCanMove = AxisValue != 0.f;

    if (bCanMove)
    {
        FRotator ControllerRotation = GetControlRotation();
        FRotator YawRotation = FRotator(0.f, ControllerRotation.Yaw, 0.f);
        FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        AddMovementInput(Direction, AxisValue);
    }
}

void ASoulsPlayerCharacter::MoveRight(float AxisValue)
{
    bool bCanMove = AxisValue != 0.f;

    if (bCanMove)
    {
        FRotator ControllerRotation = GetControlRotation();
        FRotator YawRotation = FRotator(0.f, ControllerRotation.Yaw, 0.f);
        FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(Direction, AxisValue);
    }
}

void ASoulsPlayerCharacter::LookUp(float AxisValue)
{
    bool bCanRotate = AxisValue != 0.f;

    if (bCanRotate)
    {
        float DeltaPitchRotation = AxisValue * GetWorld()->GetDeltaSeconds();
        DeltaPitchRotation *= LookUpRate;

        AddControllerPitchInput(DeltaPitchRotation);
    }
    
}

void ASoulsPlayerCharacter::Turn(float AxisValue)
{
    bool bCanRotate = AxisValue != 0.f;

    if (bCanRotate)
    {
        float DeltaPitchRotation = AxisValue * GetWorld()->GetDeltaSeconds();
        DeltaPitchRotation *= LookUpRate;

        AddControllerYawInput(DeltaPitchRotation);
    }
}