// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnableAttackCollisionNotify.h"
#include "Animation/HumanAnimInstanceInterface.h"

void UEnableAttackCollisionNotify::NotifyBegin(USkeletalMeshComponent* MeshComp,
                            UAnimSequenceBase* Animation, float TotalDuration)
{
    if (MeshComp)
    {
        auto AnimInstance = MeshComp->GetAnimInstance();
        auto AnimInterface = Cast<IHumanAnimInstanceInterface>(AnimInstance);

        if (AnimInterface)
        {
            IHumanAnimInstanceInterface::Execute_EnableAttackCollision(AnimInstance);
        }
    } 
}

void UEnableAttackCollisionNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, 
                                            UAnimSequenceBase* Animation)
{

    if (MeshComp)
    {
        auto AnimInstance = MeshComp->GetAnimInstance();
        auto AnimInterface = Cast<IHumanAnimInstanceInterface>(AnimInstance);

        if (AnimInterface)
        {
            IHumanAnimInstanceInterface::Execute_DisableAttackCollision(AnimInstance);
        }
    }
}