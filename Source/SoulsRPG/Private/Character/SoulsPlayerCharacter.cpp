// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SoulsPlayerCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ASoulsPlayerCharacter::ASoulsPlayerCharacter()
{
    bUseControllerRotationYaw = false;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->TargetArmLength = 300.f;
    SpringArm->bInheritYaw = true;

    FollowCamera = CreateDefaultSubobject <UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(SpringArm, SpringArm->SocketName);
}