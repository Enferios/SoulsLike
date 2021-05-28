// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/FootStepSoundNotify.h"

#include "Character/BaseCharacterInterface.h"

void UFootStepSoundNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    AActor* Pawn = MeshComp->GetOwner();

    bool bImplementsInterface = Pawn->Implements<UBaseCharacterInterface>();
    if (bImplementsInterface)
    {
        IBaseCharacterInterface::Execute_FootstepNotify(Pawn);
    }
}