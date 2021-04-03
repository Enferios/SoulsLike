// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/UnequipWeaponNotify.h"

#include "Animation/HumanAnimInstanceInterface.h"

void UUnequipWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && Animation)
	{
		auto AnimInstance = MeshComp->GetAnimInstance();
		auto AnimInterface = Cast<IHumanAnimInstanceInterface>(AnimInstance);

		if (AnimInterface)
		{
			IHumanAnimInstanceInterface::Execute_UnequipWeapon(AnimInstance);
		}
	}
}

