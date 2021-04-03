// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EquipWeaponNotify.h"

#include "Animation/HumanAnimInstanceInterface.h"

void UEquipWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && Animation)
	{
		UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
		if (AnimInstance)
		{
			auto AnimInterface = Cast<IHumanAnimInstanceInterface>(AnimInstance);

			if (AnimInterface)
			{
				IHumanAnimInstanceInterface::Execute_EquipWeapon(AnimInstance);
			}
		}
	}
}