// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AttackSoundNotify.h"

#include "Character/PlayerCharacterInterface.h"

void UAttackSoundNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animtaion)
{
	if (MeshComp)
	{
		AActor* Pawn = MeshComp->GetOwner();

		bool bImplements = Pawn->Implements<UPlayerCharacterInterface>();
		if (bImplements)
		{
			IPlayerCharacterInterface::Execute_PlayAttackSound(Pawn);
		}

	}
}