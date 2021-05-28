// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BlockInputNotifyState.h"

#include "Character/PlayerCharacterInterface.h"

void UBlockInputNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float Duration)
{
	if (MeshComp)
	{

		AActor* OwnerPawn = MeshComp->GetOwner();

		bool bImplements = OwnerPawn->Implements<UPlayerCharacterInterface>();

		if (bImplements)
		{
			IPlayerCharacterInterface::Execute_BlockPlayerInput(OwnerPawn);
		}
	}
}

void UBlockInputNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{	
		AActor* OwnerPawn = MeshComp->GetOwner();

		bool bImplements = OwnerPawn->Implements<UPlayerCharacterInterface>();

		if (bImplements)
		{
			IPlayerCharacterInterface::Execute_EnablePlayerInput(OwnerPawn);
		}
	}
}
