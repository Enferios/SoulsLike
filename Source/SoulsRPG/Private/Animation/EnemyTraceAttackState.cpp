// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyTraceAttackState.h"

#include "Character/EnemyCharacterInterface.h"

void UEnemyTraceAttackState::NotifyBegin(USkeletalMeshComponent* MeshComp, 
                             UAnimSequenceBase* Animation, float TotalDuration)
{
    if (MeshComp)
    {
        AActor* Pawn = MeshComp->GetOwner();

        if (Pawn->Implements<UEnemyCharacterInterface>())
        {
            IEnemyCharacterInterface::Execute_StartAttackTrace(Pawn);
        }
    }
}

void UEnemyTraceAttackState::NotifyEnd(USkeletalMeshComponent* MeshComp, 
                                        UAnimSequenceBase* Animation)
{
    if (MeshComp)
    {
        AActor* Pawn = MeshComp->GetOwner();

        if (Pawn->Implements<UEnemyCharacterInterface>())
        {
            IEnemyCharacterInterface::Execute_StopAttackTrace(Pawn);

        }
    }
}
